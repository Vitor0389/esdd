
Nesse trabalho prático, implementamos o algoritmo Quick Sort de forma não recursiva (iterativa).


Nomes: Caio Vitor Soares, Bernardo F. Filho, Vitor M. Calicchio

Nesse trabalho implementamos um programa para simular uma fila de um banco, conforme características a seguir:

O banco possui duas filas de clientes, uma para o público geral e outra para prioridades. Essas duas filas são atendidas pelos caixas do banco.
Ao liberar um caixa, um cliente da fila é chamado, atendendo às seguintes restrições:
Se a fila de prioridades está vazia, sempre é chamado o primeiro da fila geral
Se a fila de prioridades não estiver vazia, o cliente dessa fila é chamado, desde que não tenha sido chamado três clientes prioridades de forma seguida. Ou seja, se três prioridades forem chamados seguidamente, um cliente da fila geral deve ser chamado. Após isso, novos clientes prioridades podem ser chamados novamente.


| Entrada     | Saída      |
|------------|-----------|
| g Rodrigo  | Joel      |
| g Bia      | Frederico |
| p Joel     | Luciana   |
| s          | Rodrigo   |
| g Fatima   | Fabiana   |
| p Frederico | Elen     |
| p Luciana  | Fabio     |
| s          | Bia       |
| s          | Fatima    |
| p Fabiana  | Valter    |
>>>>>>> trabalho4esdd/main

