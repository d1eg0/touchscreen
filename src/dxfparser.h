#include <dxflib/dl_creationadapter.h>
//using namespace std;
class DxfParser: public DL_CreationAdapter
{
public:
    DxfParser();
    virtual void addLayer   (const DL_LayerData& data);
    virtual void addLine    (const DL_LineData& data);
};


