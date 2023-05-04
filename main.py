import pygame
from pygame import gfxdraw

def to_short(n1, n2):
    return (n1 << 8) + n2
def to_shorts(lst: list[int]):
    return [to_short(a, b) for a, b in zip(lst[::2], lst[1::2])]

with open("testing.bin", "rb") as file:
    vals = [b for b in file.read()]
    width = to_short(vals[0], vals[1])
    height = to_short(vals[2], vals[3])
    fps = to_short(vals[4], vals[5])
    screen = pygame.display.set_mode((width, height))
    clock = pygame.time.Clock()
    clock.tick(fps)
    vals = vals[6:]
    while True:
        for a, a1, b, b1, c, c1, d, d1 in [vals[i:i + 8] for i in range(0, len(vals), 8)]:
            nums = to_shorts([a, a1, b, b1, c, c1, d, d1])
            match nums[0]:
                case 0:
                    r = nums[3] & 0xf00 >> 4
                    g = (nums[3] & 0xf0)
                    b = (nums[3] & 0xf) << 4

                    gfxdraw.pixel(screen, nums[1], nums[2], (r, g, b))
                case 1:
                    clock.tick()
                    pygame.display.flip()
            for e in pygame.event.get():
                if e.type == pygame.QUIT:
                    exit()