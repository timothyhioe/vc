import cv2
import numpy as np

print("OpenCV-Version: " + cv2.__version__)
img = cv2.imread("yoshi.png")
cv2.imshow("image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()

#aufgabe 2

# Get the image dimensions
height, width, channels = img.shape
print(f"Width: {width}, Height: {height}, Channels: {channels}")


# Convert the image to float32 format
img_float = img.astype(np.float32)
print("Converted image data type:", img_float.dtype)


# Display uint8 image
cv2.imshow("Image (uint8)", img)
cv2.waitKey(0)

# Display float32 image (rescale to 0-255 for visualization)
cv2.imshow("Image (float32)", np.uint8(img_float))
cv2.waitKey(0)

cv2.destroyAllWindows()

# Calculate the center of the image
center_x, center_y = width // 2, height // 2

# Define the square's top-left and bottom-right corners
start_x, start_y = center_x - 5, center_y - 5
end_x, end_y = center_x + 5, center_y + 5

# Draw the red square
cv2.rectangle(img, (start_x, start_y), (end_x, end_y), (0, 0, 255), -1)
cv2.imshow("Image with Red Square", img)
cv2.waitKey(0)
cv2.destroyAllWindows()


# Set every 5th row to black
img[::5, :] = 0
cv2.imshow("Image with Black Rows", img)
cv2.waitKey(0)
cv2.destroyAllWindows()


# Save the modified image
cv2.imwrite("modified_yoshi.png", img)
print("Image saved as 'modified_yoshi.png'")


#aufgabe 3

# Load Yoshi image and mask
yoshi = cv2.imread("yoshi.png")
mask = cv2.imread("mask.png", cv2.IMREAD_GRAYSCALE)  # Load mask as grayscale

if yoshi is None or mask is None:
    print("Error: One or both images could not be loaded!")
    exit()

# Convert Yoshi image to HSV color space
yoshi_hsv = cv2.cvtColor(yoshi, cv2.COLOR_BGR2HSV)

# Identify white pixels in the mask (value = 255)
white_pixels = (mask == 255)

# Change the H (hue) value for the corresponding pixels
new_hue = 120  # Example hue value for purple
yoshi_hsv[white_pixels, 0] = new_hue  # Update hue channel

# Convert back to BGR for display
yoshi_bgr_modified = cv2.cvtColor(yoshi_hsv, cv2.COLOR_HSV2BGR)

# Display the modified image
cv2.imshow("Modified Yoshi", yoshi_bgr_modified)
cv2.waitKey(0)
cv2.destroyAllWindows()

# Optional: Add a trackbar for interactive hue adjustment
def update_hue(val):
    yoshi_hsv[white_pixels, 0] = val
    updated_bgr = cv2.cvtColor(yoshi_hsv, cv2.COLOR_HSV2BGR)
    cv2.imshow("Modified Yoshi with Slider", updated_bgr)

cv2.namedWindow("Modified Yoshi with Slider")
cv2.createTrackbar("Hue", "Modified Yoshi with Slider", 0, 179, update_hue)

# Set initial hue value and show image
cv2.setTrackbarPos("Hue", "Modified Yoshi with Slider", new_hue)
cv2.imshow("Modified Yoshi with Slider", yoshi_bgr_modified)
cv2.waitKey(0)
cv2.destroyAllWindows()

#save the modified yoshi if want
cv2.imwrite("modified_yoshi_hue.png", yoshi_bgr_modified)
print("Modified image saved as 'modified_yoshi_hue.png'")

#aufgabe 4
import cv2
import numpy as np

img_input = cv2.imread("FigSource.png")
img_target = cv2.imread("FigTarget.png")


img_input_LAB = cv2.cvtColor(img_input, cv2.COLOR_BGR2LAB)
img_target_LAB = cv2.cvtColor(img_target, cv2.COLOR_BGR2LAB)

input_L_channel, input_A_channel, input_B_channel = cv2.split(img_input_LAB)
target_L_channel, target_A_channel, target_B_channel = cv2.split(img_target_LAB)

def adjustChannels(input_channel, target_channel):
    #subtract mean
    input_mean = np.mean(input_channel)
    input_channel = input_channel - input_mean

    #standard deviation
    input_std = np.std(input_channel)
    input_channel = input_channel / input_std

    #multiply input and std target
    target_std = np.std(target_channel)
    input_channel = input_channel * target_std

    #add mittelwert des Targets zum input
    target_mean = np.mean(target_channel)
    input_channel = input_channel + target_mean

    return input_channel

adjusted_l = adjustChannels(input_L_channel, target_L_channel)
adjusted_a = adjustChannels(input_A_channel, target_A_channel)
adjusted_b = adjustChannels(input_B_channel, target_B_channel)

adjusted_lab = cv2.merge((adjusted_l, adjusted_a, adjusted_b))
adjusted_lab = np.clip(adjusted_lab, 0, 255)
adjusted_lab = adjusted_lab.astype(np.uint8)

adjusted_RGB = cv2.cvtColor(adjusted_lab, cv2.COLOR_LAB2BGR)

cv2.imshow("Original image", img_input)
cv2.imshow("Target image", img_target)
cv2.imshow("Adjusted Image", adjusted_RGB)
cv2.waitKey(0)
cv2.destroyAllWindows()





