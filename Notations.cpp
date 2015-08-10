#include <iostream>
#include <string>
#include <stack>
using namespace std;

stack<char> CargarDatos(string nodos)//Procedimiento que separa los caracteres de un string y los almacena en una pila.
{
	stack<char> myStack;
	
	for (int i=0;i<nodos.size();i++)
	{
		myStack.push(nodos[i]);
	}

	return myStack;
}

template <typename type>

class treeNode//Declaracion de la clase nodo del arbol
{
	public:
		//Atributos
		type data;
		int altura;//Indica la altura del nodo
		treeNode<type> *leftPtr;//Apuntador a hijo izq
		treeNode<type> *rigthPtr;//Apuntador a Hmno derecho
		//Metodos
		treeNode()//Constructor sin parametros, inicializa los auntadores a null
		{
			leftPtr=NULL;
			rigthPtr=NULL;
		}
		
		treeNode(type value, int alt)//Constructor parametrizado que asigna un valor al dato y una altura al nodo
		{
			data=value;
			altura=alt;
			leftPtr=NULL;
			rigthPtr=NULL;
		}
};

template <typename type>
class tree//Declaracion de la clase arbol general que en este caso sera un arbol binario
{
	public:
		//Atributos
		treeNode<type> *root;//unico atribut que es a raiz de arbol, de el se derivan los demas nodos
		//Metodos
		tree();//Constructor parametrizado que crea una raiz vacia = NULL
		tree(type value,int alt);//Constructor parametrizado que asigna uuna altura y un valor a la raiz
		bool esVacio(treeNode<type> *A);//Indica si el arbol es vacio
		void createTree(treeNode<type> *root,stack<char> &pila,int m);//Crea un arbol a partir de una pila de caracteres (arbol de expresion m-ario)
		void preOrder(treeNode<type> *root,int id);//Recorre en pre-order el arbol, luego imprie la informacion de los nodos y por ultimo destruye los mismo
		
		
};

template <typename type>

tree<type>::tree()
{
	root=NULL;
}

template <typename type>

tree<type>::tree(type value, int alt)
{
	root= new treeNode<type>(value,alt);
	root->leftPtr=NULL;
	root->rigthPtr=NULL;
}

template <typename type>

bool tree<type>::esVacio(treeNode<type> *A)
{
	return A==NULL;
}

template <typename type>

void tree<type>::createTree(treeNode<type> *root,stack<char> &pila,int m)
{
	for(int i=0;i<m;i++)//Condicion que hace que se cumple que el arbol sea m-ario
	{
		if(pila.top()=='+'||pila.top()=='*')//Si el caracter extraidod e la ila es + o *
		{
			if (root->leftPtr==NULL)//Si el padre no tiene hijos
			{
				root->leftPtr= new treeNode<type>(pila.top(),root->altura + 1);//Se crea un nuevo nodo
				pila.pop();//Se desapila en la pla
				createTree(root->leftPtr,pila,m);// llamada recursiva ahora con el ultimo valor desapilado como padre

			}else
			{
				treeNode<type> *aux;// si el padre tiene hijos

				aux=root->leftPtr;// al hijo al que apunta el padre se guarda en una variable auxiliar
				root->leftPtr=new treeNode<type>(pila.top(),root->altura + 1);//al padre se pone a apuntar a un nuevo nodo creado
				pila.pop();//Se desapila la pila
				root->leftPtr->rigthPtr=aux;//Al nuevo nodo agregad se pone a apuntar al pasado hijo del padre
				createTree(root->leftPtr,pila,m);//se hace una lalmada recursiva con el ultimo valor desapilado como adre
			}
		}else//Si el caracter extraido de la pila es un numero
		{
			if(root->leftPtr==NULL)//Si el padre no tiene hijos
			{
				root->leftPtr=new treeNode<type>(pila.top(),root->altura + 1);//se pone al padre a apuntar a su nuevo hijo
				pila.pop();//Se desapila
			}else
			{
				treeNode<type> *aux;// se crea una variable auxiliar

				aux=root->leftPtr;// Se guarda el primogenito del padre
				root->leftPtr=new treeNode<type>(pila.top(),root->altura + 1);// Se setea un nuevo primogenito
				root->leftPtr->rigthPtr=aux;// a primogenito se le asigna el primogenito anterior a su apuntador de hmno
				pila.pop();//Se desapila
			}
		}

	}

} 

template <typename type>

void tree<type>::preOrder(treeNode<type> *root, int id)
{
	if(root!=NULL)// Si el nodo es distinto de null
	{
		cout<<root->data<<"/"<<root->altura<<"/";// se imprime la info del nodo
		if(root->altura==0)
			cout<<"R";
		else
			cout<<id;
		cout<<" ";
		preOrder(root->leftPtr,0);// se hace una lamada recursiva co el hijo izq
		preOrder(root->rigthPtr,id+1);// se hace una llamada recursiva con el hmno derecho
		delete(root);// Se destruye el nodo
	}
}



int main()
{
	tree<char> *A= new tree<char>(); //Apuntador de tipo arbol
	stack<char> Pila;// se crea una pila
	string Expresion;// String de entrada
	int M,n;// M= numerod e grados del arbol, n= numero de casos

	cin>>n;//Se lee el numero de casos

	for(int i=0;i<n;i++)// Hasta cumpir con el numero de casos
	{
		cin>>M;// se lee el numero de grados del arbol
		cin>>Expresion;//Se lee la expresion

		A= new tree<char>();//Se asigna a A un nuevo espacio en memoria

		Pila=CargarDatos(Expresion);// Se lelna la pila
		A->root=new treeNode<char>(Pila.top(),0);// Se le asigna a la raiz el caracter del tpe de la pila
		Pila.pop();// Se desapila la pila

		A->createTree(A->root,Pila,M);// Se crea el arbol sobre el apuntador A

		A->preOrder(A->root,0);//Se hace el recorrido

		cout<<endl;//Salto de linea para el caso siguiente
	}

	return 0;
}