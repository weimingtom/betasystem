#include "SingletonInputMouse.hpp"

#include <memory>
#include "DxLibWrapper/InputMouse.hpp"

namespace {

std::auto_ptr<InputMouse> s_instance;

} // namespace unnamed 

void SingletonInputMouse::Init()
{
	s_instance.reset( new_InputMouse() );
}

void SingletonInputMouse::Update()
{
	if( s_instance.get() ){
		s_instance->Update();
	}
}

InputMouse* SingletonInputMouse::Get()
{
	return s_instance.get();
}

