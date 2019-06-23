#ifndef _GXO_APPLICATION_H
#define _GXO_APPLICATION_H

namespace gxo {
	class Application
	{
	public:
		Application()
		{
		}

		~Application()
		{

		}


		virtual void on_config() {

		}

		virtual void on_update() {

		}

		virtual void on_project_loaded()
		{
			
		}

		virtual void register_matedata()
		{
		}
		 


	private:
		
	};


#define APP(NAME)\
gxo::Application * gxo::gxo_create_application() {\
	auto * app= new NAME; \
	return app; \
}

extern gxo::Application* gxo_create_application();
}

#endif