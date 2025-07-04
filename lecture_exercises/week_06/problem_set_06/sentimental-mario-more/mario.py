def get_int():
    while True:
        print("Height: ", end="")
        height = input()
        try:
            height = int(height)
            if height >= 1 and height <= 8:
                return height
            else:
                raise ValueError
        except ValueError:
            print("Height must be a number between 1 and 8 (inclusive).")


def draw_piramid(height):
    height = height + 1
    for i in range(1, height):
        print(f"{" " * (height - i - 1)}{"#" * i}  {"#" * i}")


def main():
    height = get_int()
    draw_piramid(height)


main()
