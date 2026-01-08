#include <iostream>

#include "core/application.hpp"
#include "utils/metadata.hpp"
#include "utils/runtime.hpp"

using namespace crotale;

class MyMessenger : public core::System
{
public:
    // Classes derived from core::System may have any constructor
    // signature, provided that the System base class is constructed
    // with `this` as the parameter.
    //
    // Dependencies on other systems should usually be in the form of
    // a reference to that system, assigned in the constructor by the
    // require() method.
    MyMessenger() : System(this), metadata(require<utils::Metadata>())
    {
        // Event handlers usually work best with the following syntax: 
        // `add_event_handler(&<ClassName>::<method_name>);`.
        //
        // The method should not be static, and must have the signature
        // `void <method_name>(<EventT>& event);
        // where EventT is a class derived from core::Event.
        add_event_handler(&MyMessenger::on_start);
        add_event_handler(&MyMessenger::on_update);
        add_event_handler(&MyMessenger::on_quit);
    }

    void on_start(utils::Start& event)
    {
        std::cout << "This application is named " << metadata.name << ", version " << metadata.version << "!\n" <<
            "Try stopping this process with Ctrl+C.\n" << std::endl;
    }

    void on_update(utils::Update& event)
    {
        std::cout << "This application has just received an Update event!" << std::endl;
    }

    void on_quit(utils::Quit& event)
    {
        std::cout << "This application is now quitting!" << std::endl;
    }

private:
    utils::Metadata& metadata;
};

int main()
{
    // Only one Application should be constructed (multiple will overwrite
    // each other, Application is a singleton class).
    core::Application application;

    // Systems can be registered through perfect forwarding to the System's constructor.
    application.register_system<utils::Metadata>("My Application", utils::Version { 1, 0, 0 }, "MIT");
    application.register_system<utils::Runtime>(1);
    application.register_system<MyMessenger>();

    // Necessary to start the event system. Don't forget it!
    // The program will safely end, after completing the current
    // when a class call's the Application's `quit()` method.
    application.loop();
}