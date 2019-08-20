#include "random.h"

Random::Random() {}

// If a size is provided at initialisation, a vector of this size
// is created and filled with random bytes.
Random::Random(size_t n) : nBytes(n), randomBytes(n, 0) 
{
	setRandomBytes();
}

// If a buffer is provided at initialisation, it is filled with random bytes
Random::Random(std::vector<unsigned char>& buffer)
{
	setRandomBytes(std::begin(buffer), std::end(buffer));	
}

void Random::fillVector(iterator start, iterator end)
{
	setRandomBytes(start, end);
}

// Set the bytes using a static method. This design decision allows access to the
// `randomBuffer()` method from a non-object context, and minimises code duplication.
void Random::setRandomBytes(iterator start, iterator end)
{
	Random::randomBuffer(start, end);
}

// read() stores nBytes characters into the array pointed to by first param.
// To convert the iterator into a pointer, get the address of the
// dereferenced value: `&*start`. Then it needs to be cast into a pointer
// of the correct type for `std::ifstream::read()`.
void Random::randomBuffer(iterator start, iterator end)
{
	size_t nBytes = end - start;
	std::ifstream file("/dev/urandom", std::ios::binary|std::ios::in);
	if (!file)
		throw OpenFileException{};
	
	file.read((char*)&*start, nBytes);
}

// Wrapper for setRandomBytes(iterator, iterator).
void Random::setRandomBytes()
{
	setRandomBytes(std::begin(randomBytes), std::end(randomBytes));
}

std::vector<unsigned char> Random::getRandomBytes() const
{
	return randomBytes;
}

// If a suitable buffer is provided to the method, passed by reference,
// the randomBytes member is copied into the buffer.
void Random::getRandomBytes(std::vector<unsigned char>& buffer) const
{
//	setRandomBytes(std::begin(buffer), std::end(buffer));
	buffer = randomBytes;
}

void Random::printRandomBytes() const
{
	printRandomBytes(randomBytes);
}

void Random::printRandomBytes(const std::vector<unsigned char>& v) const
{
	for (auto& el : v) {
		std::cout << std::setw(2) << std::setfill('0')
		       << std::hex << (int)el;
	}
	std::cout << '\n';
}

void setBuffer(std::vector<unsigned char>& buffer)
{
	Random::randomBuffer(std::begin(buffer), std::end(buffer));
}
