
#include "string.h"
#include <iostream>
#include <cstring>


// A few freebies to get past the first couple of tests.
// These may need to be modified!
sfw::string::string(void)
{
	// TODO: is this finished?
	m_data = new char[m_size = 1]{ '\0' };
}

sfw::string::~string()
{
	// TODO: is this finished?
	delete[] m_data;
}

size_t sfw::string::length() const
{
	// TODO: is this finished?
	return strlen(m_data);
}





sfw::string::string(size_t size)
{
	// TODO:
	
	if (!size)
		m_size = 1;
	else
		m_size = size;
	m_data = new(std::nothrow) char[m_size];
	if (m_data == nullptr)
		m_data = new char[m_size = 1];
	*m_data = '\0';
}

sfw::string::string(const char * a, size_t size)
{
	// TODO:
	if (a != nullptr)
	{
		if (!size)
			m_size = 1;
		else
			m_size = size;
		m_data = new(std::nothrow) char[m_size];
		if (m_data == nullptr)
			m_data = new char[m_size = 1]{ '\0' };
		else
		{
			*m_data = '\0';
			strncpy_s(m_data, m_size, a, size - 1);
			m_data[length()] = '\0';
		}
	}
	else
		m_data = new char[m_size = 1]{ '\0' };

}

sfw::string::string(const char * a)
{
	// TODO:
	if (a != nullptr)
	{
		m_size = strlen(a) + 1;
		m_data = new(std::nothrow) char[m_size];
		if (m_data == nullptr)
			m_data = new char[m_size = 1]{ '\0' };
		else
		{
			*m_data = '\0';
			strncpy_s(m_data, m_size, a, strlen(a) + 1);
			m_data[m_size - 1] = '\0';
		}
	}
	else
		m_data = new char[m_size = 1]{ '\0' };
}

sfw::string::string(const string & a)
{
	// TODO:
	if (this->m_data != a.m_data)
	{
		m_size = a.m_size;
		m_data = new(std::nothrow) char[m_size];
		if (m_data == nullptr)
			m_data = new char[m_size = 1]{ '\0' };
		else
		{
			*m_data = '\0';
			strncpy_s(m_data, m_size, a.m_data, a.m_size);
			m_data[m_size - 1] = '\0';
		}
	}
	else
	{
		m_data = new char[m_size = 1]{ '\0' };
	}
}

sfw::string::string(string && a)
{
	// TODO:
	m_size = a.m_size;
	m_data = a.m_data;
	a.m_data = new char[a.m_size = 1]{ '\0' };
}

sfw::string & sfw::string::operator=(const char * a)
{
	// TODO:
	if (a == nullptr)
	{
		resize(1);
		return *this;
	}
	if (m_data != a)
	{
		resize(strlen(a) + 1);
		strncpy_s(m_data, m_size, a, strlen(a));
		m_data[strlen(a)] = '\0';
	}
	return *this;
}

sfw::string & sfw::string::operator=(const string & a)
{
	// TODO:
	if (m_data != a.m_data)
	{
		if (a.m_size == 1)
			resize(1);
		else
		{
			resize(a.m_size);
			strncpy_s(m_data, m_size, a.m_data, a.m_size);

		}
	}
	return *this;
}

sfw::string & sfw::string::operator=(string && a)
{
	// TODO:
	if (m_data != a.m_data)
	{
		delete[] m_data;
		m_size = a.m_size;
		m_data = a.m_data;
		a.m_data = new char[a.m_size = 1]{ '\0' };
	}
	return *this;
}

sfw::string & sfw::string::operator+=(const string & a)
{
	// TODO:
	resize(length() + a.m_size);
	strncat_s(m_data, m_size, a.m_data,a.m_size);
	return *this;
}

sfw::string & sfw::string::operator+=(const char * a)
{
	// TODO:
	resize(length() + strlen(a) + 1);
	strncat_s(m_data, m_size, a, strlen(a) + 1);
	return *this;
}

sfw::string & sfw::string::operator+=(char a)
{
	// TODO:
	resize(length() + 2);
	m_data[length()] = a;
	m_data[length() + 1] = '\0';
	return *this;
}

char & sfw::string::operator[](size_t index)
{
	// TODO: Is this finished?
	return this->m_data[index];
}

const char & sfw::string::operator[](size_t index) const
{
	// TODO: Is this finished?
	return this->m_data[index];
}




size_t sfw::string::size() const
{
	// TODO:
	return m_size;
}

void sfw::string::resize(size_t size)
{
	// TODO:
	if (!size)
	{
		delete[] m_data;
		m_data = new char[m_size = 1]{ '\0' };
		return;
	}
	else
		m_size = size;

	char *temp = new(std::nothrow) char[m_size];
	if (temp == nullptr)
	{
		resize(1);
		return;
	}
	*temp = '\0';
	if (length() >= size)
	{
		if (*m_data != '\0');
		strncpy_s(temp, size, m_data, size - 1);
		temp[size - 1] = '\0';
	}
	else
	{
		strncpy_s(temp, size, m_data, length());
		temp[length()] = '\0';
	}
	delete[] m_data;
	m_data = temp;
	temp = nullptr;
	
}

void sfw::string::clear()
{
	// TODO:
	m_data[0] = '\0';
}

bool sfw::string::empty() const
{
	// TODO:
	if (m_data[0] == '\0')
		return true;
	else
		return false;
}


const char * sfw::string::cstring() const
{
	// TODO:
	return m_data;
}

bool sfw::operator<(const string & a, const string & b)
{
	// TODO:
	if (strcmp(a.cstring(), b.cstring()) == -1)
		return true;
	else
		return false;
}

bool sfw::operator<(const string & a, const char * b)
{
	// TODO:
	if (strcmp(a.cstring(), b) == -1)
		return true;
	else
		return false;
}

bool sfw::operator<(const char * a, const string & b)
{
	// TODO:
	if (strcmp(a, b.cstring()) == -1)
		return true;
	else
		return false;
}

bool sfw::operator<=(const string & a, const string & b)
{
	// TODO:
	if (a < b || a == b)
		return true;
	else
		return false;
}

bool sfw::operator<=(const string & a, const char * b)
{
	// TODO:
	if (a < b || a == b)
		return true;
	else
		return false;
}

bool sfw::operator<=(const char * a, const string & b)
{
	// TODO:
	if (a < b || a == b)
		return true;
	else
		return false;
}

bool sfw::operator>(const string & a, const string & b)
{
	// TODO:
	if (a <= b)
		return false;
	else
		return true;
}

bool sfw::operator>(const string & a, const char * b)
{
	// TODO:
	if (a <= b)
		return false;
	else
		return true;
}

bool sfw::operator>(const char * a, const string & b)
{
	// TODO:
	if (a <= b)
		return false;
	else
		return true;
}

bool sfw::operator>=(const string & a, const string & b)
{
	// TODO:
	if (a < b)
		return false;
	else
		return true;
}

bool sfw::operator>=(const string & a, const char * b)
{
	// TODO:
	if (a < b)
		return false;
	else
		return true;
}

bool sfw::operator>=(const char * a, const string & b)
{
	// TODO:
	if (a < b)
		return false;
	else
		return true;
}

bool sfw::operator!=(const string & a, const string & b)
{
	// TODO:
	if (a == b)
		return false;
	else
		return true;
}

bool sfw::operator!=(const string & a, const char * b)
{
	// TODO:
	if (a == b)
		return false;
	else
		return true;
}

bool sfw::operator!=(const char * a, const string & b)
{
	// TODO:
	if (a == b)
		return false;
	else
		return true;
}

bool sfw::operator==(const string & a, const string & b)
{
	// TODO:
	if (!strcmp(a.cstring(), b.cstring()))
		return true;
	else
		return false;
}

bool sfw::operator==(const string & a, const char * b)
{
	// TODO:
	if (!strcmp(a.cstring(), b))
		return true;
	else
		return false;
}

bool sfw::operator==(const char * a, const string & b)
{
	// TODO:
	if (!strcmp(a, b.cstring()))
		return true;
	else
		return false;
}

sfw::string sfw::operator+(const string & a, const string & b)
{
	// TODO:
	return string(a) += b;
}

sfw::string sfw::operator+(const string & a, const char * b)
{
	// TODO:
	return string(a) += b;
}

sfw::string sfw::operator+(const char * a, const string & b)
{
	// TODO:
	return string(a) += b;
}

sfw::string sfw::operator+(const string & a, char b)
{
	// TODO:
	return string(a) += b;
}

sfw::string sfw::operator+(char a, const string & b)
{
	// TODO:
	return (string() += a)+=b;
}

std::ostream & sfw::operator<<(std::ostream & os, const string & p)
{
	// TODO:
	os << p.cstring();
	return os;
}

std::istream & sfw::operator>>(std::istream & is, string & p)
{
	// TODO:
	char tmp[255];
	is >> tmp;
	p = tmp;
	return is;
}

const sfw::string sfw::literals::operator""_sfw(const char * a, size_t len)
{
	// TODO:
	return string(a, len + 1);
}
