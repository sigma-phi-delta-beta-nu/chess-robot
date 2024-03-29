import serial
import time

## State 0 of the user interface task
S0_HOME             = 0
## State 1 of the user interface task
S1_BUTTON           = 1
## State 2 of the user interface task
S2_MOVE             = 2
## State 3 of the user interface task
S3_WAIT             = 3

MAX_BUFF_LEN = 255
port = serial.Serial("/dev/cu.usbserial-0001", 115200, timeout=1)
# port = serial.Serial("COM3", 115200, timeout=1)


def task_chess(state = S0_HOME):
    read_serial()
    reading = ""
    while True:
        if state == S0_HOME:
            print(state)
            if port.in_waiting == 0:
                write_serial("homx")
            #write_serial("homy")
            #time.sleep(0.1)
            if port.out_waiting == 0 and reading != "done":
                # while reading != "done":
                reading = read_serial()
            #time.sleep(0.01)
            #print(reading)
            else:
                reading = ""
                state = S1_BUTTON
        elif state == S1_BUTTON:
            print(state)
            # write_serial("wait")
            # while reading != "push":
            #     #print(port.out_waiting)
            #     #print(port.in_waiting)
            #     reading = read()
            #     #print(reading)
            time.sleep(0.1)
            if port.in_waiting == 0:
                write_serial("homx")
            #time.sleep(0.1)
            #write_serial("homy")
            if port.out_waiting == 0 and reading != "done":
                # while reading != "done":
                    reading = read_serial()
                #time.sleep(0.01)
                    #print(reading)
            else:
                reading = ""
                state = S2_MOVE
        elif state == S2_MOVE:
            print("S2")
            if port.in_waiting == 0:
                move_x("A")
            # time.sleep(0.1)
            #move_y("1")
            if port.out_waiting == 0:
                while reading != "done":
                    reading = read_serial()
                #time.sleep(0.01)
                state = S3_WAIT
        elif state == S3_WAIT:
            print("S3")
            pass

def read_serial(num_char=4):
    string = port.read(num_char)
    return string.decode()

def write_serial(cmd):
    cmd = cmd + '\n'
    port.write(cmd.encode())

def echo_test():
    cmd = input("enter command here: ")
    if cmd:
        write_serial(cmd)

    string = read_serial(MAX_BUFF_LEN)
    if (len(string)):
        print(string)

def home_y():
    write_serial("homy")

def read():
    # while True:
    var = read_serial()
    # print(var)
    if (len(var) and "done" in var):
        var = ""
        #print(var)
        return "done"
    if (len(var) and "push" in var):
        var = ""
        return "push"

def close():
    # this will close the claw to pick up the piece
    # move servo some distance
    # serial print the task is done
    write_serial("clos")

    # wait until the C++ code is done doing stuff and read done

    # This should read done
    # string1 = read_serial(MAX_BUFF_LEN)
    # if(len(string1)):
    #     print(string1)


def open():
    # this will open the cLAW
    # move the servo some distance
    # serial print done
    write_serial("open")


# def put_down():
#     write_serial("drop")


# def pick_up():
#     print("pick up piece")
#     write_serial("pick")


# def take_photo():
#     photo = "get photo"
#     print("have photo")
#     return photo


# def find_pieces(image):
#     # use image to find all pieces
#     photo = take_photo()
#     print("use matlab script")
#     print("returns chessboard string")
#     out = "123"
#     return out


# def validate_board(chess_str):
#     print("validate chess string")
#     return False


# # combine move and capture
# def make_move(board_str, piece1_loc, goal_loc, piece2_loc=None):
#     # no capture happens, as there is no second piece inputted
#     if (piece2_loc == None):
#         print(piece1_loc)
#         write_serial(piece1_loc)
#         pick_up()
#         print("go to end location")
#         print(goal_loc)
#         write_serial(goal_loc)
#         put_down()

#     # piece 1 captures piece 2
#     # capture happens and the piece1 is going to piece2 square
#     else:
#         print("go to piece2")
#         print(piece2_loc)
#         write_serial(piece2_loc)
#         pick_up()
#         print("go to graveyard")
#         write_serial("grav")
#         put_down()
#         print("go to piece1")
#         print(piece1_loc)
#         write_serial(piece1_loc)
#         pick_up()
#         print("go to goal")
#         print(goal_loc)
#         write_serial(goal_loc)
#         put_down()


# def move(piece_loc, goal_loc):
#     write_serial("move," + piece_loc + "," + goal_loc)
#     i = 0
#     while(i<30):
#         if read_serial(4) == "done":
#             done_flag = 1
#             break
#         else:
#             done_flag = 0
#             i += 1
#     if done_flag == 0:
#         pass

def move_x(x_loc):
    write_serial("movx," + x_loc)

def move_y(y_loc):
    write_serial("movy," + y_loc)

# def capture(board_str, piece1_loc, piece2_loc):
#     print("go to piece2")
#     print(piece2_loc)
#     write_serial(piece2_loc)
#     pick_up()
#     print("go to graveyard")
#     write_serial("grav")
#     put_down()
#     print("go to piece1")
#     print(piece1_loc)
#     write_serial(piece1_loc)
#     pick_up()
#     print("go to piece1")
#     print(piece2_loc)
#     write_serial(piece2_loc)
#     put_down()


# def castle(board_str, king_loc, rook_loc, side):
#     print("go to correct king")
#     print(king_loc)
#     pick_up()
#     print("go to proper square")
#     print(side)
#     put_down()
#     print("go to correct rook")
#     print(rook_loc)
#     pick_up()
#     print("go to proper square")
#     print(side)
#     put_down()


# def promote(board_str, piece_loc, piece_type):
#     print("go to proper piece type")
#     print(piece_type)
#     pick_up()
#     print("go to where the piece is being promoted")
#     print(piece_loc + "one more space")
#     put_down()
#     print("go to promoted piece location")
#     print(piece_loc)
#     pick_up()
#     print("go to graveyard")
#     put_down()

task_chess()

# i = 0
# read_serial()
# while(True):
#     if(port.in_waiting == 0):
#         write_serial("done")
#     if(port.out_waiting == 0):
#         var = read_serial(1000)
#     #if (len(var) and "install" not in var):
#     print(var)
#     i += 1

