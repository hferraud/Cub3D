# Cub3D
cub3d is a simple 3D game engine written in C using the Raycasting technique.
# Cub3d Multiplayer
## Installation
To install cub3D multiplayer, first clone the repository:
```bash
git clone https://github.com/Mururoahh/Cub3D.git
cd Cub3D
```
To get the server executable, run the following command:
```bash
make server
```
To get the client executable, run the following command:
```bash
make client
```
## Usage
### Map format
To run the server you need to have a correctly formated map:
* Filename with .cub extension
* The head of the file contain the identifier and path of the textures:
  * NO: north wall texture
  * SO: south wall texture
  * EA: east wall texture
  * WE: west wall texture
  * D: door texture
  * F: floor texture
  * C: ceilling texture
* The map content:
  * ` `: empty cell
  * `1`: wall
  * `0`: floor
  * `C`: closed door
  * `O`: open door
  * `A`: ammo
  * `M`: medic kit
  * `P`: pistol
  * `R`: assault rifle
  * `N` `S` `E` `W`: player spawn facing cardinal points

The map file should be formatted as follows:
```bash
NO asset/texture/TILE_1A.xpm
SO asset/texture/TILE_1E.xpm
EA asset/texture/TILE_2A.xpm
WE asset/texture/TILE_2E.xpm
F asset/texture/FLOOR_2E.xpm
C asset/texture/PIPES_1A.xpm
D asset/texture/DOOR_1B.xpm

        1111111111111111111111111
        1E0000000M1100A00000M0001
        1011000001110R01000010001
        10R100A00W0O0000P000000W1
111111111011000001110000M00000001
1A000000001100000111C111111111111
1111N111111111011100000010R01
11110111111111011101010010001
11000000110101011100A00010001
1A0000000W00A0000C000000E0001
1000P000000000001101M10010001
11000001110101011111011110P0111
1111M111 1110101 101111010001
11111111 1111111 111111111111
```
### Launch server
Run the following command:
```bash
./cub3D_server path_to_map.cub port
```
It display all the IP address available and the port to connect to.
### Launch client
Run the following command:
```bash
./cub3D server_ip server_port
```
It will establish connection with the server, load texture asset and launch the game.
## Controls
|Control             |Description                            |
|:------------------:|---------------------------------------|
| `W` `A` `S` `D`    | Move forward, left, right or backward |
| `←` `→`            | Rotate the camera left or right       |
| `Space`            | Shoot                                 |
| `F`                | Interact with door                    |
| `1` `2` `3`        | Change weapon                         |
| `M`                | Enable / Disable mouse                |
| `Right click`      | Shoot                                 |
| `Esc`              | Exit the game                         |
## Source
The textures of weapons come from '[Forgive me father](https://bytebarrel.com/forgive-me-father)' game.
## Contributing
If you notice a bug or if you have an idea to improve the project, you can create an issue on the Github repository.

Also if you'd like to contribute to Cub3D Multiplayer, feel free to fork the repository and submit a pull request.
## Contributors
* [Hugo Ferraud](https://github.com/Mururoahh)

* [Ethan Delage](https://github.com/EthanDelage)
