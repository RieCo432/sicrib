def hsv_to_rgb(H, S=1.0, V=1.0):
    H %= 360

    C = V * S
    X = C * (1 - abs((H / 60) % 2 - 1))
    m = V - C

    _R = 0
    _G = 0
    _B = 0

    if 0 <= H < 60:
        _R = C
        _G = X
    elif 60 <= H < 120:
        _R = X
        _G = C
    elif 120 <= H < 180:
        _G = C
        _B = X
    elif 180 <= H < 240:
        _G = X
        _B = C
    elif 240 <= H < 300:
        _R = X
        _B = C
    elif 300 <= H < 360:
        _R = C
        _B = X

    R = int((_R + m) * 255)
    G = int((_G + m) * 255)
    B = int((_B + m) * 255)

    return R, G, B


def rgb_to_hsv(rgb):

    R = rgb[0] / 255.0
    G = rgb[1] / 255.0
    B = rgb[2] / 255.0

    cmax = max(R, G, B)
    cmin = min(R, G, B)
    diff = cmax - cmin

    if cmax == cmin:
        H = 0
    elif cmax == R:
        H = (60 * ((G - B) / diff) + 360) % 360
    elif cmax == G:
        H = (60 * ((B - R) / diff) + 120) % 360
    elif cmax == B:
        H = (60 * ((R - G) / diff) + 240) % 360

    if cmax == 0:
        S = 0
    else:
        S = diff / cmax

    V = cmax

    return H, S, V

def RGB_to_color(r, g, b):
    """Convert three 8-bit red, green, blue component values to a single 24-bit
    color value.
    """
    return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF)


if __name__ == "__main__":

    print(hsv_to_rgb(0))
    print(hsv_to_rgb(120))
    print(hsv_to_rgb(240))
    print(hsv_to_rgb(60))
    print(hsv_to_rgb(180))
    print(hsv_to_rgb(300))
