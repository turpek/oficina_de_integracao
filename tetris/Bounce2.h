#ifndef BOUNCE2_H
#define BOUNCE2_H

namespace Bounce2 {
    class Button {
    public:
        // Variáveis públicas que os testes podem alterar diretamente:
        // - Quando mockIsPressed for true, isPressed() vai retornar true.
        // - Quando mockPressed for true, pressed() vai retornar true.
        // - Quando mockReleased for true, released() vai retornar true.
        bool mockIsPressed = false;
        bool mockPressed   = false;
        bool mockReleased  = false;
        int call_update = 0;
    
        // Construtor (pode não ser necessário, mas adicionei para clareza)
        Button() = default;
    
        // Simula o método attach(pin, mode) da Bounce2::Button
        void attach(int /*pin*/, int /*mode*/) {
            // nenhum comportamento; somente para satisfazer a interface
        }
    
        // Simula o método interval(ms) da Bounce2::Button
        void interval(unsigned long /*ms*/) {
            // nenhum comportamento; somente para satisfazer a interface
        }
    
        // Simula o método update() da Bounce2::Button
        void update() {
            call_update++;
        }
    
        // Retorna true se o botão estiver "pressionado"
        bool isPressed() const {
            return mockIsPressed;
        }
    
        // Retorna true se o botão acabou de ser pressionado
        bool pressed() const {
            return mockPressed;
        }
    
        // Retorna true se o botão acabou de ser solto
        bool released() const {
            return mockReleased;
        }
    
        void setPressedState(int value){
        }
    
    };
}

#endif
