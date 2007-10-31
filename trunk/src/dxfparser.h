#include <dxflib/dl_creationadapter.h>
#include <stack>
//using namespace std;
class DxfParser: public DL_CreationAdapter
{
public:
    string nombre;
    DxfParser();
    virtual void addLayer   (const DL_LayerData& data);
    virtual void addLine    (const DL_LineData& data);
    virtual void addPolyline    (const DL_PolylineData& data);
    virtual void addVertex  (const DL_VertexData& data);
    virtual void addBlock(const DL_BlockData& data);
};


