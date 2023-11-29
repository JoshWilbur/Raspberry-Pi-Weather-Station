
// Define a struct to hold CO2 and TVOC values
struct SGP30Values {
    unsigned int co2;
    unsigned int tvoc;
};

// Function declarations
void sgp30Init(int file);
struct SGP30Values sgp30Measure(int file);


