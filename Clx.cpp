#include "Clx.h"

Clx::Prc::PrcData::PrcData()
{
}

Clx::Prc::PrcData::~PrcData()
{
}

Clx::Prc::Prc()
{
}

Clx::Prc::~Prc()
{
}

Clx::Prc::PrcData::Prl::Prl()
{
}

Clx::Prc::PrcData::Prl::~Prl()
{
}

Clx::Prc::PrcData::Prl::Sprm::Sprm()
{
}

Clx::Prc::PrcData::Prl::Sprm::~Sprm()
{
}

Clx::Pcdt::PlcPcd::Pcd::FcCompressed::FcCompressed()
{
}

Clx::Pcdt::PlcPcd::Pcd::FcCompressed::~FcCompressed()
{
}

Clx::Pcdt::PlcPcd::Pcd::Prm::Prm()
{
}

Clx::Pcdt::PlcPcd::Pcd::Prm::~Prm()
{
}

Clx::Pcdt::PlcPcd::Pcd::Pcd()
{
}

Clx::Pcdt::PlcPcd::Pcd::~Pcd()
{
}

Clx::Pcdt::PlcPcd::PlcPcd()
{
}

Clx::Pcdt::PlcPcd::~PlcPcd()
{
}

Clx::Pcdt::Pcdt()
{
}

Clx::Pcdt::~Pcdt()
{
}

Clx::Clx()
{
}

Clx::~Clx()
{
}

VOID Clx::readToClx(std::ifstream &stream, DWORD lcb)
{
	stream.read(reinterpret_cast<char *>(this), lcb);
	return;
}
