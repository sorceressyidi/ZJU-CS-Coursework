import cv2
if __name__ == "__main__":
	img = cv2.imread("input.png")
	cv2.imwrite("test.bmp", img)
