/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:12:17 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/04 15:48:26 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _storage()
{
    std::cout << "[ Default constructor called! ]" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << "[ Destructor called! ]" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _storage(copy._storage)
{
    std::cout << "[ Copy constructor called! ]" << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
    std::cout << "[ Overload assignation operator called! ]" << std::endl;
    if (this != &src) {
        this->_storage = src._storage;
    }
    else {
        std::cout << "[ Same info. Copy abort! ]" << std::endl;
    }
    return (*this);
}

/* Setter. */
void BitcoinExchange::setter(std::string &date, double &value)
{
    _storage[date] = value;
}

/* Funcion para leer el archivo '.csv' y almacenar sus valores en el contenedor tipo 'map' de la clase. */
void BitcoinExchange::reading(void)
{
    std::ifstream csv;
    csv.open("data.csv");
    if (!csv)
    {
        std::cout << "Error: there's no file to open." << std::endl;
        return ;
    }
    std::string line;
    std::string date;
    double value;
    while (std::getline(csv, line))                 // Leemos el archivo usando 'getline' y almacenamos el contenido en 'line'.
    {
        std::istringstream new_line(line);          // Creamos un nuevo objeto tipo 'istringstream' a partir de cada linea leida. Con este objeto podremos extraer datos de los valores de la linea leida.
        if (std::getline(new_line, date, ','))      // Si la condicion de usar 'getline' para leer desde 'new_line' y almacenar en 'date' usando la pipe como delimitador es OK... 
        {
            new_line >> value;                      // ... entonces leemos el valor de 'new_line' y lo almacenamos en 'value'.
            setter(date, value);                    // Por ultimo usamos el 'setter' y almacenamos los valores en el contenedor '_storage' de la parte privada de la clase.
        }
        //std::cout << std::fixed << std::setprecision(2) << date << " | " << value << std::endl;    // DEBUG!!!
    }
}

/* Funcion para comparar los valores de '_storage' (usando la funcion 'reading') y de 'input'. */
void BitcoinExchange::processing(std::string input)
{
    reading();
    std::ifstream file;
    file.open(input.c_str());
    if (!file) {
        std::cout << "Error: there's no file to open." << std::endl;
        return ;
    }
    std::string line;
    std::string date;
    double value;
    while(std::getline(file, line))
    {
        std::istringstream new_line(line);
        if (std::getline(new_line, date, ','))
        {
            new_line >> value;
            if (_storage.find(date) != _storage.end())
            {
                if (_storage[date] == value)
                    std::cout << date << " | " << value << " | " << "OK" << std::endl;
                else
                    std::cout << date << " | " << value << " | " << "KO" << std::endl;
            }
            else
                std::cout << date << " | " << value << " | " << "KO" << std::endl;
        }
    }
}

/* Funcion para comprobar los dias de los meses segun el año. */
int BitcoinExchange::checkDate(int year, int month, int day)
{
    switch (month)
	{
		case 1:     // Meses que deben tener 30 dias.
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		{
			if (day > 31 || day <= 0)
				return (1);
			break ;
		}
		case 4:    // Meses que deben tener 29 dias.
		case 6:
		case 9:
		case 11:
		{
			if (day > 30 || day <= 0)
				return (1);
			break ;
		}
		case 2:   // Mes que puede tener 28 o 29 dias segun si el año es bisiesto.
		{
			if (year % 400 == 0 || (year % 4 == 0 && (year % 100 != 0)))
			{
				if (day > 29 || day <= 0)
					return (1);
			}
			else
			{
				if (day > 28 || day <= 0)
					return (1);
			}
			break ;
		}
		default:
			return (1);
	}
	return (0);
}

int BitcoinExchange::parseDate(std::string date)
{
    int year;
    int month;
    int day;
    std::string year_str;
    std::string month_str;
    std::string day_str;
    year_str = atoi(date.substr(0, 4));
    month_str = atoi(date.substr(5, 2));
    day_str = atoi(date.substr(8, 2));
    if (checkDate(year, month, day) == 1)
        return (0);
    
    return (1);
}