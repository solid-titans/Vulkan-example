#ifndef utilities_hpp
#define utilities_hpp

// Indeces (localizacoes) das filas das familias (e se existem)
struct QueueFamilyIndices {
    int graphicsFamily = -1;           // Localizacao da Familia das filas Graficas

    // Checar se as filas das familias sao validas
    bool isValid() {
        return graphicsFamily >= 0;

    }
};


#endif