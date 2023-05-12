import serial
import time

MAX_BUFF_LEN = 255
port = serial.Serial("/dev/cu.usbserial-0001", 115200, timeout=1)
# port = serial.Serial("COM9", 115200, timeout=1)


def read_serial(num_char=28):
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


def put_down():
    write_serial("drop")


def pick_up():
    print("pick up piece")
    write_serial("pick")


def take_photo():
    photo = "get photo"
    print("have photo")
    return photo


def find_pieces(image):
    # use image to find all pieces
    photo = take_photo()
    print("use matlab script")
    print("returns chessboard string")
    out = "123"
    return out


def validate_board(chess_str):
    print("validate chess string")
    return False


# combine move and capture
def make_move(board_str, piece1_loc, goal_loc, piece2_loc=None):
    # no capture happens, as there is no second piece inputted
    if (piece2_loc == None):
        print(piece1_loc)
        write_serial(piece1_loc)
        pick_up()
        print("go to end location")
        print(goal_loc)
        write_serial(goal_loc)
        put_down()

    # piece 1 captures piece 2
    # capture happens and the piece1 is going to piece2 square
    else:
        print("go to piece2")
        print(piece2_loc)
        write_serial(piece2_loc)
        pick_up()
        print("go to graveyard")
        write_serial("grav")
        put_down()
        print("go to piece1")
        print(piece1_loc)
        write_serial(piece1_loc)
        pick_up()
        print("go to goal")
        print(goal_loc)
        write_serial(goal_loc)
        put_down()


def move(board_str, piece_loc, goal_loc):
    print(piece_loc)
    pick_up()
    print("go to end location")
    print(goal_loc)
    put_down()


def capture(board_str, piece1_loc, piece2_loc):
    print("go to piece2")
    print(piece2_loc)
    write_serial(piece2_loc)
    pick_up()
    print("go to graveyard")
    write_serial("grav")
    put_down()
    print("go to piece1")
    print(piece1_loc)
    write_serial(piece1_loc)
    pick_up()
    print("go to piece1")
    print(piece2_loc)
    write_serial(piece2_loc)
    put_down()


def castle(board_str, king_loc, rook_loc, side):
    print("go to correct king")
    print(king_loc)
    pick_up()
    print("go to proper square")
    print(side)
    put_down()
    print("go to correct rook")
    print(rook_loc)
    pick_up()
    print("go to proper square")
    print(side)
    put_down()


def promote(board_str, piece_loc, piece_type):
    print("go to proper piece type")
    print(piece_type)
    pick_up()
    print("go to where the piece is being promoted")
    print(piece_loc + "one more space")
    put_down()
    print("go to promoted piece location")
    print(piece_loc)
    pick_up()
    print("go to graveyard")
    put_down()

i = 1
while(i < 2):
    if i <= 1:
        close()
        print(read_serial())
        open()
        print(read_serial())
        # if read_serial() == "ESP: Done\n":
        #     print(read_serial())
        # else:
        #     break
        i += 1
    else:
        break
# print(read_serial())
# print(read_serial())
