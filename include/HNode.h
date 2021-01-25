
template<class T>
class H_Node
{
public:
	H_Node*		m_pNext;
	H_Node*		m_pPrev;
	T*			m_pdata;

	static int icount;
public:

	H_Node();
	~H_Node();
};

template<class T>
H_Node<T>::H_Node()
{
	m_pdata = 0;
	m_pPrev = m_pNext = 0;

}

template<class T>
H_Node<T>::~H_Node()
{
	delete m_pdata;
}
