#include <iostream>
#include <optional>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <vector>

enum class Status
{
	good,
	notgood,
	empty
};

struct SState
{
	size_t S;
	size_t Y;
	Status status = Status::good;
	friend bool operator==(const SState& lhs, const SState& rhs);
	bool operator<(const SState& other) const {// 0 0 0 1
		if (other.status > status)
		{
			return true;
		}
		if (other.status == status && S < other.S)
		{
			return true;
		}
		if (other.status == status && S == other.S && Y < other.Y)
		{
			return true;
		}
		return false;
	};
	friend std::ifstream& operator>>(std::ifstream& in, SState& s);
};



template <typename T>
std::optional<T> OpenFile(const std::string& name)
{
	T output;
	output.open(name);
	if (!output.good())
	{
		return std::nullopt;
	}
	return output;
};

bool getKAndM(std::ifstream& str, size_t& k, size_t& m) 
{
	/*std::regex reg("^[ ]*([0-9]*)[ ]*([0-9]*)[ ]*$");
	std::cmatch cm;*/
	try
	{
		int _k;
		str >> _k;
		if (str.fail())
		{
			return false;
		}
		int _m;
		str >> _m;
		if (str.fail())
		{
			return false;
		}
		k = _k;
		m = _m;
	}
	catch (...)
	{
		return false;
	}
	str.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return true;
}

bool windTheThread(std::ifstream& str, std::set<SState>& setOfStates, size_t k, size_t m)
{
	//std::regex reg("");
	for (size_t i = 0; i < k; i++)
	{
	}
	return false;
}

int main()
{
	auto inFile = OpenFile<std::ifstream>("in.txt");
	/*if (inFile == NULL)
	{
	}*/
	auto outFile = OpenFile<std::ofstream>("out.txt");
	size_t k = 0;
	size_t m = 0;
	std::set<SState> setOfStates;
	std::set<int> hj;
	std::map<size_t, std::vector<SState>> column;
	std::map<SState, std::string> gmap;
	char buf = ' ';
	size_t stateNum = 0;
	
	if (getKAndM(inFile.value(), k, m))
	{
		for (size_t i = 0; i < k; i++)
		{
			std::vector<SState> perehody;
			for (size_t l = 0; l < m; l++)
			{
				SState g;
				inFile.value() >> g;
				setOfStates.insert(g);
				hj.insert(stateNum);
				perehody.push_back(g);
			}
			column.insert({ stateNum, perehody });
			stateNum++;
		}
		size_t i = 0;
		for (auto h = setOfStates.begin(); h != setOfStates.end(); h++)
		{
			std::string p = "g" + std::to_string(i);
			if (h->status == Status::empty)
			{
				gmap.insert({ *h, "-" });
			}
			else
			{
				gmap.insert({ *h, p });
				i++;
			}
			
		}
		for (auto& g : setOfStates)
		{
			if (g.status == Status::empty)
			{
				continue;
			}
			auto elem = column[g.S];
			outFile.value() << "Y" + std::to_string(g.Y) + " ";
			for (auto& t : elem)
			{
				if (t.status == Status::empty)
				{
					outFile.value() << "-"
									<< " ";
				}else
				{

					outFile.value() << gmap[t] << " ";
				}
			}
			outFile.value() << std::endl;
		}
		return 0;
	}
	return 1;

}

inline bool operator==(const SState& lhs, const SState& rhs)
{
	return (lhs.S == rhs.S) && (lhs.Y == rhs.Y) && (lhs.status == rhs.status);
}
inline std::ifstream& operator>>(std::ifstream& in, SState& state)
{
	std::cmatch cm;
	std::regex reg("[Ss]([0-9]+)");
	std::regex reg2("[-][,]?");
	std::string buf;
	state = { 0, 0, Status::good };
	in >> buf;
	std::cout << buf << std::endl;
	auto stat = Status::good;
	if (std::regex_match(buf.c_str(), cm, reg2))
	{  
		state.status = Status::empty;
		in >> buf;
		if (std::regex_match(buf.c_str(), cm, reg2))
		{
			state.status = Status::empty;
			return in;
		}
		in.setstate(std::ios::failbit);
		return in;
	}
	size_t s = 0;
	auto _state = std::ios::goodbit;
	if (std::regex_match(buf.c_str(),cm, reg))
	{
		s = std::stoi(cm[1]);
	}
	else
	{
		_state = std::ios::failbit;
	}
	in >> buf;
	std::cout << buf << std::endl;
	/*if (std::regex_match(buf.c_str(), cm, reg2))
	{
		state.status = Status::empty;
	}*/
	std::regex reg1("[Yy]([0-9]+[,]?)");
	size_t y = 0;
	if (std::regex_match(buf.c_str(), cm, reg1))
	{
		y = std::stoi(cm[1]); 
	}
	else
	{
		_state = std::ios::failbit;
	}
	if (_state == std::ios::goodbit)
	{
		state.S = s;
		state.Y = y;
	}
	in.setstate(_state);
	return in;
}
