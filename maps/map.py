from PIL import Image
import time
image = Image.open('maps/map.png')


print("test")
pixels = list(image.getdata())


print(pixels[0])

file = open("maps/default.txt", "w")
file.write("")
file.close()

file = open("maps/default.txt", "a")
compteur = 0
ligne = 0
for pixel in pixels:
    if pixel[0] == 0 and pixel[1] == 0 and pixel[2] == 0 and pixel[3] != 0:
        file.write("1")
    elif pixel[0] == 255 and pixel[1] == 0 and pixel[2] == 0:
        file.write("2")
    elif pixel[0] == 0 and pixel[1] == 255 and pixel[2] == 0 and pixel[3] > 80:
        file.write("3")
    else:
        file.write("0")
    compteur += 1
    if compteur % 26 == 1 and compteur != 1:
        file.write("\n")
        ligne += 1
    print(pixel, ligne)
    
    
file.close()

image.close()
