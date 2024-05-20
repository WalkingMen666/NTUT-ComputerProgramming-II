#include <stdio.h>

#define GATEVALUE(Gate) int(*GateValue)()

typedef struct _Gate {
    int input1;
    int input2;
    GATEVALUE(Gate);
}Gate;

int GateORValue(Gate *gate) {
    return (gate->input1 | gate->input2);
}

int GateANDValue(Gate *gate) {
    return (gate->input1 & gate->input2);
}

int GateNOTValue(Gate *gate) {
    return gate->input1 == 0 ? 1 : 0;
}

int GateBUFFERValue(Gate *gate) {
    return gate->input1;
}

void CreateGate(Gate *obj, char type, int input1, int input2) {
    obj->input1 = input1;
    obj->input2 = input2;
    
    if(type == 'A'){
        obj->GateValue = GateANDValue;
    }
    else if(type == 'O'){
        obj->GateValue = GateORValue;
    }
    else if(type == 'N'){
        obj->GateValue = GateNOTValue;
    }
    else{
        obj->GateValue = GateBUFFERValue;
    }
    obj->input1 = obj->GateValue(obj);
    printf("%d ", obj->input1);
}

int main(){
    int x1 = 0, x2 = 0, x3 = 0;
    char gate1[2], gate2[2], gate3[2];
    Gate gate;
    scanf("%d %d %d", &x1, &x2, &x3);
    scanf("%s %s %s", gate1, gate2, gate3);

    CreateGate(&gate, gate1[0], x1, NULL);
    CreateGate(&gate, gate2[0], gate.input1, x2);
    CreateGate(&gate, gate3[0], gate.input1, x3);

    return 0;
}