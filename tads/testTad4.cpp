#include "TadEjercicio4.cpp"

int main()
{
    ColaPrioridad* cp = new ColaPrioridad(10);
    cp->insertar(new Pedido{0, 3, true, "pizza"});
    cp->insertar(new Pedido{1, 5, false, "hamburguesa"});
    cp->insertar(new Pedido{2, 2, true, "papas"});
    cp->insertar(new Pedido{-1, 3, true, "ensalada"});
    
    cp->imprimir();
    cp->entregarPedido();
    cp->imprimir();
    cp->hacerParaLlevar(1);
    cp->imprimir();
}
