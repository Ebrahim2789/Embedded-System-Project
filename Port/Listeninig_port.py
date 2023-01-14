import threading
import ctypes
import json
import win32api, win32gui,win32clipboard
import mysql.connector

class Clipboard:
    def _create_window(self) -> int:
        """
        Create a window for listening to messages
        :return: window hwnd
        """
        wc = win32gui.WNDCLASS()
        wc.lpfnWndProc = self._process_message
        wc.lpszClassName = self.__class__.__name__
        wc.hInstance = win32api.GetModuleHandle(None)
        class_atom = win32gui.RegisterClass(wc)
        return win32gui.CreateWindow(class_atom, self.__class__.__name__, 0, 0, 0, 0, 0, 0, 0, wc.hInstance, None)

    def _process_message(self, hwnd: int, msg: int, wparam: int, lparam: int):
        WM_CLIPBOARDUPDATE = 0x031D
        if msg == WM_CLIPBOARDUPDATE:
            print('clipboard updated!')
            win32clipboard.OpenClipboard()
            datas=win32clipboard.GetClipboardData()
            win32clipboard.CloseClipboard()
            value = datas.split()
            json_str = json.dumps(value)
            resp = json.loads(json_str)
            for i in range(10):
                rows = resp[i]
                print(rows)
               
                output = []
                cnx = mysql.connector.connect(host='localhost',port= 3306,database= 'arduino',user='root',password='',charset='utf8',use_unicode=True,get_warnings=True)
                cur = cnx.cursor()

                 # Drop table if exists, and create it new
                stmt_drop = "DROP TABLE IF EXISTS names"
                cur.execute(stmt_drop)

                stmt_create = (
                    "CREATE TABLE names ("
                    "    id TINYINT UNSIGNED NOT NULL AUTO_INCREMENT, "
                    "    name VARCHAR(30) DEFAULT '' NOT NULL, "
                    "    info TEXT, "
                    "    times INT (3) DEFAULT '2', "
                    "PRIMARY KEY (id))"
                )
                cur.execute(stmt_create)


                # Insert 3 records
                info=resp[4]
                info1=resp[5]
                info2=resp[6]
                inf3=resp[8]
               
                
                names = (('Vehicle', info, 1), (inf3, info1, 2), ('Vehicle', info2, 3))
                stmt_insert = "INSERT INTO names (name, info, times) VALUES (%s, %s, %s)"
                cur.executemany(stmt_insert, names)
                cnx.commit()


                # Cleaning up, dropping the table again
                # cur.execute(stmt_drop)

                cur.close()
                cnx.close()
                # return output
            
        return 0



    def listen(self):
        def runner():
            hwnd = self._create_window()
            ctypes.windll.user32.AddClipboardFormatListener(hwnd)
            win32gui.PumpMessages()

        th = threading.Thread(target=runner, daemon=True)
        th.start()
        while th.is_alive():
            th.join(0.25)
        


if __name__ == '__main__':
    clipboard = Clipboard()
    clipboard.listen()
   
    # Humidity: 80.00 %Temperature: 27.00 *C 80.60 *FHeat index: 85.53 *F




    
