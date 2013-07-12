
#ifndef GALSINGLETON_H_
#define GALSINGLETON_H_

#include <iostream>
#include <assert.h>
#include <stddef.h>

namespace gal {
    template<class Class>
    class Singleton {
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
                assert(m_pInstance != NULL);
//              std::cout << "Returning new Instance of " << typeid(Class).name() << std::endl;
                return m_pInstance;
            }
        protected:
            Singleton();
            ~Singleton();
        private:
            Singleton(Singleton const&);
            Singleton& operator=(Singleton const&);
            static Class* m_pInstance;
    };

    template<class Class> Class* Singleton<Class>::m_pInstance = NULL;

}

#endif /* SINGLETON_H_ */

