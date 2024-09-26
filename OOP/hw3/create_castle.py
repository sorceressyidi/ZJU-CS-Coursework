import random

# Generate test data
def generate_test_data(num_rooms_min=5, num_rooms_max=18):
    num_rooms = random.randint(num_rooms_min, num_rooms_max)
    
    # Generate room names
    room_names = ["Lobby", "Courtyard", "Kitchen", "Dining Room", "Bedroom", "Treasure Room", "Tower", "Cellar", "Sanctum","Library", "Armory", "Chapel", "Gallery", "Garden", "Laboratory", "Study", "Workshop", "Observatory", "Crypt", "Catacombs", "Mausoleum", "Throne Room", "Ballroom", "Hallway", "Foyer", "Balcony", "Closet", "Bathroom", "Pantry", "Staircase", "Attic", "Basement", "Garage", "Greenhouse", "Conservatory", "Nursery", "Parlor", "Sitting Room", "Solar", "Vestibule", "Wine Cellar", "Billiard Room", "Game Room", "Music Room", "Theater", "Bar", "Lounge", "Office", "Den", "Studio", "Gallery", "Gym", "Sauna", "Spa", "Pool", "Hot Tub", "Courtyard", "Gazebo", "Patio", "Pergola", "Pavilion", "Arbor", "Grotto", "Fountain", "Garden", "Orchard", "Vineyard", "Pasture", "Stable", "Barn", "Shed", "Coop", "Pen", "Corral", "Kennel", "Aviary", "Aquarium", "Terrarium", "Vivarium", "Habitat", "Enclosure", "Cage", "Pen", "Stable", "Barn", "Shed", "Coop", "Pen", "Corral", "Kennel", "Aviary", "Aquarium", "Terrarium", "Vivarium", "Habitat", "Enclosure", "Cage"]
    random.shuffle(room_names)
    room_names = room_names[:num_rooms]
    
    if "Lobby" not in room_names:
        room_names[0] = "Lobby"
    # Generate connections between rooms
    connections = []
    for i in range(num_rooms):
        available_directions = ["east", "west", "up", "down"] # Available directions for current room
        num_exits = random.randint(1, min(4, num_rooms - 1)) # Ensure at least one exit and max 4 exits per room
        for _ in range(num_exits):
            direction = random.choice(available_directions) # Randomly select direction
            available_directions.remove(direction) # Remove selected direction from available directions
            exit_room = random.randint(0, num_rooms - 1)
            while exit_room == i: # Ensure exit room is not the current room
                exit_room = random.randint(0, num_rooms - 1)
            connections.append((i, direction, exit_room))
        
    # find all rooms that Lobby can reach:
    lobby_reachable = set()
    lobby_reachable.add(0)
    for connection in connections:
        if connection[0] in lobby_reachable:
            lobby_reachable.add(connection[2])
    # find remaining directions that lobby can connect to
    available_directions = ["east", "west", "up", "down"]
    for connection in connections:
        if connection[0] == 0:
            available_directions.remove(connection[1])
    if len(lobby_reachable) <3:
        for i in range(2):
            if i not in lobby_reachable:
                direction = random.choice(available_directions)
                available_directions.remove(direction)
                lobby_reachable.add(i)
                connections.append((0, direction, i))
    # Remove lobby from reachable rooms because monster and princess cannot be in lobby
    lobby_reachable.remove(0)
    # Randomly select monster room and princess room where lobby can reach
    monster_room = random.choice(list(lobby_reachable))
    lobby_reachable.remove(monster_room)
    princess_room = random.choice(list(lobby_reachable))
    # ensure princess room can reach the lobby again
    princess_reachable = set()
    princess_reachable.add(princess_room)
    for connection in connections:
        if connection[0] in princess_reachable:
            princess_reachable.add(connection[2])
    if 0 not in princess_reachable:
        for connection in connections:
            if connection[0] == princess_room:
                connections.remove(connection)
                connections.append((princess_room, connection[1], 0))
                break
    return num_rooms, room_names, connections, monster_room, princess_room


def save_test_data(num_rooms, room_names, connections, monster_room, princess_room, filename):
    with open(filename, 'w') as f:
        f.write(str(num_rooms) + '\n')
        for name in room_names:
            f.write(name + '\n')
        f.write(str(monster_room) + '\n')
        f.write(str(princess_room) + '\n')
        for connection in connections:
            f.write(' '.join(map(str, connection)) + '\n')

# Generate and save test data
num_rooms, room_names, connections, monster_room, princess_room = generate_test_data()
save_test_data(num_rooms, room_names, connections, monster_room, princess_room, 'test_data.txt')
