/*
- Definiti constructorii de initializare fara param si parametrizati, copy constructor, destructor si op =;
- Adaugati un constructor parametrizat care prin intermediul unui param bool sa atribuie valori campurilor clasei din consola (true) si din fisier (false) 
- op-- postfixat si prefixat
- op!=
- op (float)
- Transformati o metoda intr-o functie friend si 1 fct friend intr-o metoda
- Sa functioneze urmatorul demo:  Object v[n]; cin>>v[1]; cout<<v[1]; v[2]=v[3]=(v[1]+v[2]) 
- Sa testam in main functionalitatile clasei


*/

#include <iostream>
using namespace std;

class Nod
{
private:
	int info;
	Nod* next;
public:
	friend ostream& operator<<(ostream&, const Nod&);
	friend istream& operator>>(istream&, Nod&);
	Nod& operator=(const Nod&);
	Nod operator--(int);
	Nod& operator--();

	void set_nod_info(int val)
	{
		info = val;
		next = NULL;
	}

	int get_nod_info()
	{
		return info;
	}

	Nod()
	{
		//cout << "A fost apelat constructorul fara parametri" << endl;
	}

	Nod(int val)
	{
		//cout << "A fost apelat constructorul cu parametru pentru info" << endl;
		info = val;
		next = NULL;
	}
	~Nod()
	{
		//cout << "A fost apelat destructorul pentru elementul cu valoarea: " << info <<" : "<<next<< endl;
	}

	friend class Lista_circulara;

};


class Lista_circulara
{
private:
	Nod* prim, * ult;
	int length;
public:
	friend ostream& operator<<(ostream&, const Lista_circulara&);
	friend istream& operator>>(istream&, Lista_circulara&);
	Lista_circulara& operator=(const Lista_circulara&);
	const Lista_circulara operator+(const Lista_circulara&) const;
	Lista_circulara(const Lista_circulara&);

	Lista_circulara()
	{
		prim = NULL;
		ult = NULL;
		length = 0;
	}
	Lista_circulara(bool cond)
	{
		ifstream in;
		if (cond == 1)
		{
			int n;
			cin >> n;
			int val;
			this->length = 0;
			for (int i = 1; i <= n;i++)
			{
				cin>>val;
				this->add_poz(i, val);
			}
		}
		if (cond == 0)
		{
			in.open("fisier.txt");
			in.close();
		}
	}

	~Lista_circulara()
	{
		del_list_v2();
	}
	void createNod(int val)
	{
		Nod* temp = new Nod;
		temp->info = val;
		temp->next = NULL;
		if (prim == NULL)
		{
			prim = temp;
			ult = temp;
			temp = NULL;
			length++;
		}
		else
		{
			ult->next = temp;
			ult = temp;
			length++;
			ult->next = prim;
		}
	}
	void add_start(int val)
	{
		Nod* temp = new Nod;
		temp->info = val;
		temp->next = prim;
		prim = temp;
		length++;

	}
	void add_poz(int poz, int val)
	{
		if (poz > length + 1)
		{
			cout << "Se incearca adaugarea unui element pe o pozitie inexistenta, elementul va fi adaugat la final! " << endl;
		}
		Nod* pre = new Nod;
		Nod* cur = new Nod;
		Nod* temp = new Nod;
		Nod* q = new Nod;
		temp->info = val;
		temp->next = NULL;
		if (prim == NULL)
		{
			prim = temp;
			ult = temp;
			temp = NULL;
			length++;
		}
		else
		{
			if (poz = length)
			{
				ult->next = q;
				q->info = val;
				q->next = prim;
				ult = q;
				length++;
			}
			else
			{
				cur = prim;
				int i;
				for (i = 1; i < poz; i++)
				{
					pre = cur;
					cur = cur->next;
				}

				pre->next = temp;
				temp->next = cur;
				length++;
			}
		}
	}
	void del_poz(int poz)
	{
		Nod* cur = new Nod;
		Nod* prev = new Nod;
		Nod* temp = new Nod;
		if (prim == NULL)
		{
			cout << "Lista este goala!" << endl;
			return;
		}
		if (poz == 1)
		{
			temp = prim;
			prim = prim->next;
			ult->next = prim;
			delete temp;
			length--;
		}
		cur = prim;
		int i;
		for (i = 1; i < poz; i++)
		{
			prev = cur;
			cur = cur->next;
		}
		prev->next = cur->next;
		length--;
	}


	void del_list_v2()
	{
		if (prim == NULL)
		{
			cout << "Lista este goala" << endl;
			return;
		}

		Nod* temp;
		if (length == 1)
		{
			delete prim;
			length--;
		}
		else
		{
			Nod* q = prim->next;
			while (q != prim)
			{
				temp = q;
				q = q->next;
				delete temp;
				length--;
			}
			delete prim;
			prim = ult = NULL;
			length--;
		}
	}
	/*void del_list()
	{
		Nod* q = prim;
		Nod* temp = NULL;
		while (q != NULL)
		{
			temp = q->next;
			delete q;
			q = temp;
		}
		prim = NULL;
		ult = NULL;
	}*/

	void del_start()
	{
		if (prim == NULL)
		{
			cout << "Lista este goala!" << endl;
			return;
		}
		else
		{
			Nod* temp = new Nod;
			temp = prim;
			prim = prim->next;
			ult->next = prim;
			delete temp;
			length--;
		}
	}

	void del_k()
	{
		int k;
		cout << "Introduceti pasul de stergere: ";
		cin >> k;
		Nod* temp = new Nod;
		Nod* q = new Nod;
		if (k == 1)
		{
			/*while (length != 1)
			{
				cout << prim->info <<" ";
				del_start(); // De adaugat contor pentru oprire
				length--;
			}
			if (length == 1)
			{
				cout << prim->info<<" ";
				prim=NULL;
			}
		*/
			while (length != 1)
			{
				del_poz(1);
				length--;
			}
			cout << endl << "Ultimul element este: " << ult->info;
			prim = NULL;
			delete prim;
			delete ult;
			cout << endl;
			length--;
		}
		else
		{
			q = prim;
			temp = prim;
			int index = 1;
			while (index != k)
			{
				if (length == 1)
				{
					cout << q->info << endl;
					prim = NULL;
					delete prim;  //--Schimbare
					break;
				}

				q = temp;
				temp = temp->next;
				index++;
				if (index == k)
				{
					q->next = temp->next;
					cout << temp->info << " ";
					delete temp;
					temp = q->next;
					q = q->next;
					index = 1;
					length--;
				}
			}
		}
	}

	void inversare_lista()
	{
		if (prim == NULL)
			return;
		Nod* ante = NULL;
		Nod* cur = prim;
		Nod* urm;
		do {
			urm = cur->next;
			cur->next = ante;
			ante = cur;
			cur = urm;
		} while (cur != prim);

		prim->next = ante;
		prim = ante;
	}

	void afis(ostream& os) const
	{
		if (prim == nullptr)
		{
			os << "Lista este goala ";
		}
		else
		{
			if (length == 1)
			{
				cout << prim->info;
			}
			else
			{
				os << prim->info << " ";
				const Nod* q = prim->next;
				while (q != prim)
				{
					os << q->info << " ";
					q = q->next;
				}
				os << prim->info << " ";
				os << endl << "Lungimea listei este: " << length;
			}
		}

	}
};


int main()
{
	//Lista_circulara list(true);
	//list.add_start(4);
	//list.del_poz(7);
	//list.createNod(3);
	//list.createNod(4);
	//list.createNod(5);
	//list.add_poz(7, 10);
	//list.add_poz(6, 19);
	//list.add_poz(5, 20);
	//list.add_poz(4, 30);
	//cin >> list;
	//cout << list << endl;
	//list.del_poz(7);
	//list.del_start();
	//cout << endl;
	//for (int i = 1; i <= 10; i++)
	//{
	//	list.add_poz(i, i);
	//}
	//cout << list <<" "<<endl;
	//list.del_poz(1);
	//list.inversare_lista();
	//cout << list << " " << endl;
	//list.del_k();
	//list.del_list_v2();
	//cout << endl << list;
	//Lista_circulara list2;
	//cin >> list2;
	//list2.createNod(6);
	//list2.createNod(7);
	//list2.createNod(8);
	//Lista_circulara list2;
	//list2 = list;
	//cout << list2;
	//Lista_circulara list3;
	//list3 = list + list2;
	//cout << list3 << endl;
	//return 0;
	
}

ostream& operator<<(ostream& os, const Nod& n)
{
	os << n.info;
	return os;
}

istream& operator>>(istream& in, Nod& n)
{
	in >> n.info;
	return in;
}

ostream& operator<<(ostream& os, const Lista_circulara& n)
{
	n.afis(os);
	return os;
}

istream& operator>>(istream& in, Lista_circulara& n)
{
	int i;
	int nr;
	cout << "Introduceti numarul de elemente al listei: ";
	in >> nr;
	cout << endl;
	cout << "Elementele sunt: " << endl;
	int new_nod;
	for (i = 1; i <= nr; i++)
	{
		in >> new_nod;
		n.add_poz(i, new_nod);
	}
	cout << n;
	return in;
}

Nod& Nod::operator=(const Nod& a)
{
	if (this == &a)
	{
		cout << "Se incearca copierea aceluiasi obiect ";
		return *this;
	}
	this->info = a.info;
	return *this;
}

Nod Nod::operator--(int)
{
	Nod temp = *this;
	--* this;
	return temp;
}

Nod& Nod::operator--()
{
	this->info--;
	return *this;
}

Lista_circulara& Lista_circulara::operator=(const Lista_circulara& a)
{

	if (this == &a /*|| a.prim==NULL*/)
	{
		cout << "Se incearca copierea aceluiasi obiect ";
		return *this;
	}
	this->del_list_v2();
	createNod(a.prim->info);
	Nod* q = a.prim->next;
	while (q != a.prim)
	{
		createNod(q->info);
		q = q->next;
	}
	return *this;
}

const Lista_circulara Lista_circulara::operator+(const Lista_circulara& l) const
{
	Lista_circulara rezultat;
	Nod* q = prim->next;
	rezultat.createNod(prim->info);
	while (q != prim)
	{
		rezultat.createNod(q->info);
		q = q->next;
	}
	q = l.prim->next;
	rezultat.createNod(l.prim->info);
	while (q != l.prim)
	{
		rezultat.createNod(q->info);
		q = q->next;
	}
	return rezultat;
}

Lista_circulara::Lista_circulara(const Lista_circulara& a)
{
	prim = ult = NULL;
	length = 0;
	createNod(a.prim->info);
	Nod* q = a.prim->next;
	while (q != a.prim)
	{
		createNod(q->info);
		q = q->next;
	}
}