import tkinter as tk
import time
import re
import sys
from tkinter.font import Font

WINDOW_HEIGHT = 1600
WINDOW_WIDTH = WINDOW_HEIGHT + 300

COLOR_P1 = "blue"
COLOR_P2 = "red"

global PAUSED

class FrameMap():
    def __init__(self, window_ctrl, rows, columns):
        self.window_ctrl = window_ctrl
        self.rows = rows
        self.columns = columns
        self.frame = tk.Frame(self.window_ctrl.window)
        self.frame.pack(side="left")
        self.map_data = {}

        self.cell_size = (WINDOW_HEIGHT - 8) / (self.rows if self.rows > self.columns else self.columns)
        self.map_canvas = tk.Canvas(self.frame)
        self.map_canvas.configure(width=(self.cell_size * self.columns),
                                height=(self.cell_size * self.rows))
        self.map_canvas.pack(side="left")
        for column in range(self.columns):
            for row in range(self.rows):
                x1 = column * self.cell_size+4
                y1 = row * self.cell_size+4
                x2 = x1 + self.cell_size
                y2 = y1 + self.cell_size
                self.map_data[row, column] = self.map_canvas.create_rectangle(x1, y1, x2, y2, fill="black")
                # print(self.map_canvas.itemcget(self.map_data[row, column], "fill"))
        
class FrameResult():
    def __init__(self, window_ctrl, p1, p2):
        self.window_ctrl = window_ctrl
        self.p1 = p1
        self.p2 = p2
        self.frame = tk.Frame(self.window_ctrl.window)
        self.frame.pack()

        font = Font(family="Helvetica", size=20, weight="bold")
        
        label = tk.Label(self.frame, text=f"{self.p1.name}", fg = f"{self.p1.color}", font = font, justify='center').pack()

        self.score_p1 = tk.StringVar()
        self.score_p1.set(f'{0}')
        score = tk.Label(self.frame, textvariable = self.score_p1, fg = f"{self.p1.color}", font = font, justify='center').pack()

        if self.p2:
            label = tk.Label(self.frame, text=f"VS", font = font, justify='center').pack()
            
            label = tk.Label(self.frame, text=f"{self.p2.name}", fg = f"{self.p2.color}", font = font, justify='center').pack()

            self.score_p2 = tk.StringVar()
            self.score_p2.set(f'{0}')
            score = tk.Label(self.frame, textvariable = self.score_p2, fg = f"{self.p2.color}", font = font, justify='center').pack()
        else:
            self.score_p2 = None

class WindowController():
    def __init__(self):
        self.window = tk.Tk()
        self.window.geometry(f"{WINDOW_WIDTH}x{WINDOW_HEIGHT}")

    def start_loop(self):
        self.window.mainloop()
    
class Player():
    def __init__(self, id, line):
        self.id = id
        self.name = re.match(r"^.*\[(.*)\].*$", line).group(1).split("/")[-1].replace("a.out","default").replace(".filler","")

        if self.id == 1:
            self.char = 'O'
            self.color = COLOR_P1
        else:
            self.char = 'X'
            self.color = COLOR_P2

        self.score = 0

class GameController():
    def __init__(self, rows, columns, p1, p2=None):
        self.p1 = p1
        self.p2 = p2
        self.window_ctrl = WindowController()
        self.window_ctrl.window.bind("<Button-1>", self.put_in_pause)
        self.window_ctrl.window.bind("<Return>", self.go_next_step)

        self.map = FrameMap(self.window_ctrl, rows, columns)
        self.result = FrameResult(self.window_ctrl, p1, p2)

    def start(self):
        self.window_ctrl.window.after(1, self.loop_read)
        self.window_ctrl.start_loop()

    def put_in_pause(self, nooo):
        global PAUSED
        PAUSED = not PAUSED

    def go_next_step(self, nooo):
        if PAUSED:
            self.next_step()

    def loop_read(self):
        if PAUSED:
            self.window_ctrl.window.after(100, self.loop_read)
        else:
            self.next_step()
            self.window_ctrl.window.after(1, self.loop_read)

    def next_step(self):
        line = ""
        while "Plateau" not in line:
            try:
                line = input()
            except:
                return
        if "Plateau" in line:
            input()
            self.update_grid()

    def update_grid(self):
        for row in range(self.map.rows):
            line = input()[4:]
            for column in range(self.map.columns):
                if line[column].lower() in 'ox':
                    if line[column].lower() == 'o':
                        p = self.p1
                    else:
                        p = self.p2
                    if self.map.map_canvas.itemcget(self.map.map_data[row, column], "fill") != p.color:
                        self.map.map_canvas.itemconfig(self.map.map_data[row, column], fill=p.color)
                        p.score += 1

                        if line[column].lower() == 'o':
                            self.result.score_p1.set(f"{p.score}")
                        else:
                            self.result.score_p2.set(f"{p.score}")
                        self.window_ctrl.window.update_idletasks()

if __name__ == '__main__':
    if  len(sys.argv) > 1:
        try:
            i = int(sys.argv[1])
            if i <= 1000 and i >= 300:
                WINDOW_HEIGHT = i
                WINDOW_WIDTH = WINDOW_HEIGHT + 300
        except Exception as e:
            pass
    line = ""
    p1 = None
    p2 = None
    while "Plateau" not in line:
        line = input()
        if "$$$ exec p1 :" in line:
            p1 = Player(1, line)
        elif "$$$ exec p2 :" in line:
            p2 = Player(2, line)
    if "Plateau" not in line:
        print("NO PLATEAU")
        exit()
    PAUSED = False
    d = line[:-1].split(" ")
    rows= int(d[1])
    columns = int(d[2])
    the_game = GameController(rows, columns, p1, p2)
    the_game.start()