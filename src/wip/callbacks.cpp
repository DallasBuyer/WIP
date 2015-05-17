#include "callbacks.h"
#include "KeyDefinetions.h"
#include "InputManager.h"
#include "RBMath/Inc/RBMath.h"

//////////////////////////////////////////////////////////////////////////
//  glfw callback
//////////////////////////////////////////////////////////////////////////
void glfw_error_callback(int error,const char* description)
{
	printf(description);
}

void glfw_mouse_pos_callback(GLFWwindow* windows,double x,double y)
{
	g_input_manager->update_mouse((int)(short)x,(int)(short)y);
	g_input_manager->set_move(true);
}

void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//GLFW_REPEAT is useless for mouse,so we use some other way to drive mouse.
	int bits = g_input_manager->get_last_key_info()->key_bit;
	int bits_c = g_input_manager->get_last_key_info()[1].key_bit;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		if(action==GLFW_PRESS)
		{
			bits |= WIP_MOUSE_LBUTTON;
			lmouse_keep_going = true;
		}
		else if(action==GLFW_RELEASE)
		{
			bits &= ~WIP_MOUSE_LBUTTON;
			lmouse_keep_going = false;
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		if(action==GLFW_PRESS)
		{
			bits |= WIP_MOUSE_RBUTTON;
			rmouse_keep_going = true;
		}
		else if(action==GLFW_RELEASE)
		{
			bits &= ~WIP_MOUSE_RBUTTON;
			rmouse_keep_going = false;
		}
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		if(action==GLFW_PRESS)
		{
			bits |= WIP_MOUSE_MBUTTON;
			mmouse_keep_going = true;
		}
		else if(action==GLFW_RELEASE)
		{
			bits &= ~WIP_MOUSE_MBUTTON;
			mmouse_keep_going = false;
		}
		break;
	}

	g_input_manager->update(bits_c,bits);
	//printf("run\n");

}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	int bits = g_input_manager->get_last_key_info()->key_bit;
	int bits_c = g_input_manager->get_last_key_info()[1].key_bit;
	if(action==GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_A:
			bits_c |= WIP_A;
			break;
		case GLFW_KEY_B:bits_c |= WIP_B;
			break;
		case GLFW_KEY_C:bits_c |= WIP_C;
			break;
		case GLFW_KEY_D:bits_c |= WIP_D;
			break;
		case GLFW_KEY_E:bits_c |= WIP_E;
			break;
		case GLFW_KEY_F:bits_c |= WIP_F;
			break;
		case GLFW_KEY_G:bits_c |= WIP_G;
			break;
		case GLFW_KEY_H:bits_c |= WIP_H;
			break;
		case GLFW_KEY_I:bits_c |= WIP_I;
			break;
		case GLFW_KEY_J:bits_c |= WIP_J;
			break;
		case GLFW_KEY_K:bits_c |= WIP_K;
			break;
		case GLFW_KEY_L:bits_c |= WIP_L;
			break;
		case GLFW_KEY_M:bits_c |= WIP_M;
			break;
		case GLFW_KEY_N:bits_c |= WIP_N;
			break;
		case GLFW_KEY_O:bits_c |= WIP_O;
			break;
		case GLFW_KEY_P:bits_c |= WIP_P;
			break;
		case GLFW_KEY_Q:bits_c |= WIP_Q;
			break;
		case GLFW_KEY_R:bits_c |= WIP_R;
			break;
		case GLFW_KEY_S:bits_c |= WIP_S;
			break;
		case GLFW_KEY_T:bits_c |= WIP_T;
			break;
		case GLFW_KEY_U:bits_c |= WIP_U;
			break;
		case GLFW_KEY_V:bits_c |= WIP_V;
			break;
		case GLFW_KEY_W:bits_c |= WIP_W;
			break;
		case GLFW_KEY_X:bits_c |= WIP_X;
			break;
		case GLFW_KEY_Y:bits_c |= WIP_Y;
			break;
		case GLFW_KEY_Z:bits_c |= WIP_Z;
			break;
		}
	}
	if(action==GLFW_PRESS)
	{

		switch (key)
		{
		case GLFW_KEY_A:
			bits_c |= WIP_A;
			break;
		case GLFW_KEY_B:bits_c |= WIP_B;
			break;
		case GLFW_KEY_C:bits_c |= WIP_C;
			break;
		case GLFW_KEY_D:bits_c |= WIP_D;
			break;
		case GLFW_KEY_E:bits_c |= WIP_E;
			break;
		case GLFW_KEY_F:bits_c |= WIP_F;
			break;
		case GLFW_KEY_G:bits_c |= WIP_G;
			break;
		case GLFW_KEY_H:bits_c |= WIP_H;
			break;
		case GLFW_KEY_I:bits_c |= WIP_I;
			break;
		case GLFW_KEY_J:bits_c |= WIP_J;
			break;
		case GLFW_KEY_K:bits_c |= WIP_K;
			break;
		case GLFW_KEY_L:bits_c |= WIP_L;
			break;
		case GLFW_KEY_M:bits_c |= WIP_M;
			break;
		case GLFW_KEY_N:bits_c |= WIP_N;
			break;
		case GLFW_KEY_O:bits_c |= WIP_O;
			break;
		case GLFW_KEY_P:bits_c |= WIP_P;
			break;
		case GLFW_KEY_Q:bits_c |= WIP_Q;
			break;
		case GLFW_KEY_R:bits_c |= WIP_R;
			break;
		case GLFW_KEY_S:bits_c |= WIP_S;
			break;
		case GLFW_KEY_T:bits_c |= WIP_T;
			break;
		case GLFW_KEY_U:bits_c |= WIP_U;
			break;
		case GLFW_KEY_V:bits_c |= WIP_V;
			break;
		case GLFW_KEY_W:bits_c |= WIP_W;
			break;
		case GLFW_KEY_X:bits_c |= WIP_X;
			break;
		case GLFW_KEY_Y:bits_c |= WIP_Y;
			break;
		case GLFW_KEY_Z:bits_c |= WIP_Z;
			break;
		}
	}
	if(action==GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_A:
			bits_c &= ~WIP_A;
			break;
		case GLFW_KEY_B:bits_c &= ~WIP_B;
			break;
		case GLFW_KEY_C:bits_c &= ~WIP_C;
			break;
		case GLFW_KEY_D:bits_c &= ~WIP_D;
			break;
		case GLFW_KEY_E:bits_c &= ~WIP_E;
			break;
		case GLFW_KEY_F:bits_c &= ~WIP_F;
			break;
		case GLFW_KEY_G:bits_c &= ~WIP_G;
			break;
		case GLFW_KEY_H:bits_c &= ~WIP_H;
			break;
		case GLFW_KEY_I:bits_c &= ~WIP_I;
			break;
		case GLFW_KEY_J:bits_c &= ~WIP_J;
			break;
		case GLFW_KEY_K:bits_c &= ~WIP_K;
			break;
		case GLFW_KEY_L:bits_c &= ~WIP_L;
			break;
		case GLFW_KEY_M:bits_c &= ~WIP_M;
			break;
		case GLFW_KEY_N:bits_c &= ~WIP_N;
			break;
		case GLFW_KEY_O:bits_c &= ~WIP_O;
			break;
		case GLFW_KEY_P:bits_c &= ~WIP_P;
			break;
		case GLFW_KEY_Q:bits_c &= ~WIP_Q;
			break;
		case GLFW_KEY_R:bits_c &= ~WIP_R;
			break;
		case GLFW_KEY_S:bits_c &= ~WIP_S;
			break;
		case GLFW_KEY_T:bits_c &= ~WIP_T;
			break;
		case GLFW_KEY_U:bits_c &= ~WIP_U;
			break;
		case GLFW_KEY_V:bits_c &= ~WIP_V;
			break;
		case GLFW_KEY_W:bits_c &= ~WIP_W;
			break;
		case GLFW_KEY_X:bits_c &= ~WIP_X;
			break;
		case GLFW_KEY_Y:bits_c &= ~WIP_Y;
			break;
		case GLFW_KEY_Z:bits_c &= ~WIP_Z;
			break;
		}
	}
	g_input_manager->update(bits_c,bits);
}

void glfw_scroll_callback(GLFWwindow* window, double x, double y)
{
	//x not used.
	int bits = g_input_manager->get_last_key_info()->key_bit;
	int bits_c = g_input_manager->get_last_key_info()[1].key_bit;
	if(RBMath::is_nearly_equal(y,1.0))
	{
		bits |= WIP_MOUSE_SCROLLER_UP;
		//printf("up\n");
	}
	else if(RBMath::is_nearly_equal(y,-1.0))
	{
		bits |= WIP_MOUSE_SCROLLER_DOWN;
		//printf("down\n");
	}
	g_input_manager->update(bits_c,bits);
	//printf("%08x at %0.3f: Scroll: %0.3f %0.3f\n", counter++, glfwGetTime(), x, y);
}
