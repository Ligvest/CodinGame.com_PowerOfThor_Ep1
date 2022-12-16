#include <iostream>
#include <array>
#include <string>
#include <string_view>

struct Vector2D {
	float X;
	float Y;
};

enum class EDirection {
	NoMove = 0b0000,
	West = 0b0001,
	East = 0b0010,
	North = 0b0100,
	South = 0b1000,
	NorthEast = 0b0110,
	SouthEast = 0b1010,
	NorthWest = 0b0101,
	SouthWest = 0b1001
};

inline EDirection operator | (const EDirection Left, const EDirection Right) {
	size_t Result;
	Result = static_cast<size_t>(Left) | static_cast<size_t>(Right);
	return static_cast<EDirection>(Result);
}

inline EDirection operator |= (EDirection& Left, const EDirection Right) {	
	Left = Left | Right;
	return Left;
}


static std::array<std::string, 0b1111> DirectionToStringArray;
std::string_view MakeMove(Vector2D& CurrentLocation, const Vector2D& Destination);

int main()
{
	DirectionToStringArray[static_cast<size_t>(EDirection::NoMove)] = "NoMove";
	DirectionToStringArray[static_cast<size_t>(EDirection::West)] = "W";
	DirectionToStringArray[static_cast<size_t>(EDirection::East)] = "E";
	DirectionToStringArray[static_cast<size_t>(EDirection::North)] = "N";
	DirectionToStringArray[static_cast<size_t>(EDirection::South)] = "S";
	DirectionToStringArray[static_cast<size_t>(EDirection::NorthEast)] = "NE";
	DirectionToStringArray[static_cast<size_t>(EDirection::SouthEast)] = "SE";
	DirectionToStringArray[static_cast<size_t>(EDirection::NorthWest)] = "NW";
	DirectionToStringArray[static_cast<size_t>(EDirection::SouthWest)] = "SW";

	Vector2D LightLocation; // The position of the light of power
	Vector2D ThorLocation; // Thor's position
    std::cin >> LightLocation.X >> LightLocation.Y >> ThorLocation.X >> ThorLocation.Y; 
	std::cin.ignore();

    // game loop
    while (1) {
        size_t RemainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        std::cin >> RemainingTurns; 
		std::cin.ignore();

	    std::string_view NextDirection = MakeMove(ThorLocation, LightLocation);
        std::cout << NextDirection << '\n';
    }
}

std::string_view MakeMove(Vector2D& CurrentLocation, const Vector2D& Destination) {
	EDirection DirectionToMove = EDirection::NoMove;

	float XOffset = CurrentLocation.X - Destination.X;
	float YOffset = CurrentLocation.Y - Destination.Y;

	if (XOffset > 0) {
		DirectionToMove |= EDirection::West;
		--CurrentLocation.X;
	}
	if (XOffset < 0) {
		DirectionToMove |= EDirection::East;
		++CurrentLocation.X;
	}
	if (YOffset > 0) {
		DirectionToMove |= EDirection::North;
		--CurrentLocation.Y;
	}
	if (YOffset < 0) {
		DirectionToMove |= EDirection::South;
		++CurrentLocation.Y;
	}

	return DirectionToStringArray[static_cast<size_t>(DirectionToMove)];
}