#ifndef _GXO_ID_H
#define _GXO_ID_H
namespace gxo {
	typedef unsigned int GPUID;
	typedef unsigned int UID;
	class ID
	{
	public:
		unsigned int id;
	public:
		ID(unsigned int id)
		{
			id = id;
		}

		~ID()
		{
		}

	private:

	};
}
#endif