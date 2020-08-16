from circular_list import CircularList
from room import Room
from compass import DataFlow, Direction
from edge import Edge


def build_living_room():

    vertical_length = 69
    horizontal_length_short = 108
    horizontal_length_long = 149

    s0 = Edge(horizontal_length_long, Direction.N, DataFlow.W_TO_E)
    s90 = Edge(horizontal_length_short, Direction.E, DataFlow.N_TO_S)
    s180 = Edge(horizontal_length_long, Direction.S, DataFlow.E_TO_W)
    s270 = Edge(horizontal_length_short, Direction.W, DataFlow.S_TO_N)

    s45 = Edge(vertical_length, Direction.NE, DataFlow.FLOOR_TO_CEIL)
    s135 = Edge(vertical_length, Direction.SE, DataFlow.FLOOR_TO_CEIL)
    s225 = Edge(vertical_length, Direction.SW, DataFlow.FLOOR_TO_CEIL)
    s315 = Edge(vertical_length, Direction.NW, DataFlow.FLOOR_TO_CEIL)

    living_room = Room(4 * vertical_length + 2 * horizontal_length_short + 2 * horizontal_length_long,
                       s0, s45, s90, s135, s180, s225, s270, s315, init_philips_hue=True,
                       philips_hue_ip="192.168.178.2", light_names=["Living Room Light"])

    #living_room = Room(4 * vertical_length + 2 * horizontal_length_short + 2 * horizontal_length_long,
    #                   s0, s45, s90, s135, s180, s225, s270, s315)

    living_room.set_sequences(living_room.north_east, living_room.north, living_room.north_west, living_room.west,
                              living_room.south_west, living_room.south, living_room.south_east, living_room.east,
                              living_room.north, living_room.west, living_room.south, living_room.east,
                              living_room.north_east, living_room.north_west, living_room.south_west,
                              living_room.south_east)

    living_room.allocate_leds()

    return living_room
