/*
 * GalaxyApplicationBase.h
 *
 *  Created on: Jul 12, 2013
 *      Author: nicholaskell
 */

#ifndef GALAXYAPPLICATIONBASE_H_
#define GALAXYAPPLICATIONBASE_H_

#include <cstddef>

namespace gal {

    template<class Class>
//    typedef  void (Class::*FredMemFn)(void);
    /*
     *
     */
    class GalaxyApplicationBase {
        public:

            static Class* getInstance() {
                //              std::cout << "Fetching an Instance of " << typeid(Class).name() << std::endl;
                if (!m_pInstance) {
                    //                  std::cout << "Instantiating  " << typeid(Class).name() << std::endl;
                    m_pInstance = new Class;
                    //                  std::cout << "Instantiated " << typeid(Class).name()<< std::endl;
                } else {
                    //                  std::cout << "Fetching an old Instance of " << typeid(Class).name() << std::endl;
                }
//                assert(m_pInstance != NULL);
                //              std::cout << "Returning new Instance of " << typeid(Class).name() << std::endl;
                return m_pInstance;
            }

//            void doIt(){};
//            void draw(){};
//            virtual void idle()=0;

            static void idleMethod() {
//                void (Class::*tmp)() = (Class::getInstance()->idleMethodPtr);
//                Class* tmpClass = Class::getInstance();
//                (tmpClass->*tmp)();
                (Class::getInstance()->*(Class::getInstance()->idleMethodPtr))();
            }

            static void drawMethod() {
                //                void (Class::*tmp)() = (Class::getInstance()->drawMethodPtr);
                //                Class* tmpClass = Class::getInstance();
                //                (tmpClass->*tmp)();

                (Class::getInstance()->*(Class::getInstance()->drawMethodPtr))();

                //                (Class::getInstance()->(Class::getInstance()->drawMethodPtr))();
            }

            static void setupMethod() {
                //                void (Class::*tmp)() = (Class::getInstance()->drawMethodPtr);
                //                Class* tmpClass = Class::getInstance();
                //                (tmpClass->*tmp)();

                (Class::getInstance()->*(Class::getInstance()->setupMethodPtr))();

                //                (Class::getInstance()->(Class::getInstance()->drawMethodPtr))();
            }

        protected:

            GalaxyApplicationBase() {
                this->idleMethodPtr = &Class::idle;
                this->drawMethodPtr = &Class::draw;
                this->setupMethodPtr = &Class::setup;
            }
            ;
            ~GalaxyApplicationBase() {
            }
            ;
            void (Class::*setupMethodPtr)(void);
            void (Class::*drawMethodPtr)(void);
            void (Class::*idleMethodPtr)(void);
        private:
            GalaxyApplicationBase(GalaxyApplicationBase const&);
            GalaxyApplicationBase& operator=(GalaxyApplicationBase const&);
            static Class* m_pInstance;
    };

    template<class Class> Class* GalaxyApplicationBase<Class>::m_pInstance =
            NULL;

} /* namespace gal */
#endif /* GALAXYAPPLICATIONBASE_H_ */
