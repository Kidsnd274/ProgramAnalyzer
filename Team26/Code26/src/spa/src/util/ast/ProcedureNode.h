#include <string>
#include "TNode.h"

class ProcedureNode : public TNode {
private:
    std::string procedureName;

public:
    ProcedureNode(int sN, std::string pN) : TNode(sN) {
        procedureName = pN;
    }
};