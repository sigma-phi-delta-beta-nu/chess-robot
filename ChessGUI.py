import pygame
import os

# Set up the Pygame window
pygame.init()
WIDTH, HEIGHT = 640, 640
WINDOW = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Chess Game')

# Load the chess piece images
IMAGES = {}
for piece in ['wp', 'wR', 'wN', 'wB', 'wQ', 'wK', 'bp', 'bR', 'bN', 'bB', 'bQ', 'bK']:
    image_path = os.path.join('images', f'{piece}.png')
    IMAGES[piece] = pygame.image.load(image_path)

# Set up the chess board
board = [
    ['bR', 'bN', 'bB', 'bQ', 'bK', 'bB', 'bN', 'bR'],
    ['bp', 'bp', 'bp', 'bp', 'bp', 'bp', 'bp', 'bp'],
    ['--', '--', '--', '--', '--', '--', '--', '--'],
    ['--', '--', '--', '--', '--', '--', '--', '--'],
    ['--', '--', '--', '--', '--', '--', '--', '--'],
    ['--', '--', '--', '--', '--', '--', '--', '--'],
    ['wp', 'wp', 'wp', 'wp', 'wp', 'wp', 'wp', 'wp'],
    ['wR', 'wN', 'wB', 'wQ', 'wK', 'wB', 'wN', 'wR']
]

# Define some colors
WHITE = (233, 198, 175)
BLACK = (160, 90, 44)
GREY = (128, 128, 128)

# Define the size of each square on the chess board
SQUARE_SIZE = HEIGHT // 8

# Draw the chess board
def draw_board():
    for row in range(8):
        for col in range(8):
            color = WHITE if (row + col) % 2 == 0 else BLACK
            pygame.draw.rect(WINDOW, color, (col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))
            piece = board[row][col]
            if piece != '--':
                img = IMAGES[piece]
                img = pygame.transform.scale(img, (SQUARE_SIZE, SQUARE_SIZE))
                WINDOW.blit(img, (col * SQUARE_SIZE, row * SQUARE_SIZE))

# Main game loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Draw the chess board
    draw_board()

    # Update the Pygame window
    pygame.display.update()

# Quit Pygame
pygame.quit()


def fen_to_board(fen):
    board = []
    for row in fen.split('/'):
        board_row = []
        for char in row:
            if char.isdigit():
                board_row.extend(['--'] * int(char))
            else:
                board_row.append(char)
        board.append(board_row)
    return board
