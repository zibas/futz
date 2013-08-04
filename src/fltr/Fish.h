#include "GameBase.h"
#include "Futz.h"
#include "math/Vector3.h"

class Fish {
    private:
    Vector3 drag;
    float mass;

    Vector3 position;
    Vector3 thrust;
    Vector3 lastThrust;
    Vector3 velocity;
    Vector3 acceleration;

    float speed;

    public:
	Node* node;
	Model* model;


        void Load(){
            Futz* futz = Futz::Instance();

            drag = Vector3();
            position = Vector3();
            thrust = Vector3();
            lastThrust = Vector3();
            velocity = Vector3();
            acceleration = Vector3();

            drag.x = 2;
            drag.y = 3;
            drag.z = 0; 

            speed = 5;

            char* file = (char*)"assets/plane.obj";
            model = futz->LoadModel(file);
            model->Load();
            node = new Node();
            node->AddModel(model);
            node->transform.SetScale(1);
            node->transform.SetPosition(0,0,0);
            futz->scene.AddNode(node);
        }

        void ThrustOn(double x, double y){
            x *= speed; 
            y *= speed; 
            if(x != 0){
                thrust.x = x;
            }
            if ( y != 0 ){
                thrust.y = y;
            }
            thrust.z = 0;
        }

        void Update(){
            Futz* futz = Futz::Instance();
            //node->transform.AddRelativeTranslation(1*futz->time.delta,0,0);
            PhysicsUpdate();
            node->transform.SetPosition(position.x, position.y, position.z);
            thrust.x = 0;
            thrust.y = 0;
            thrust.z = 0;
        }

        void PhysicsUpdate(){
            Futz* futz = Futz::Instance();
            float delta = futz->time.delta;
            acceleration = thrust;
            velocity = velocity + (acceleration * delta);
            position = position + (velocity * delta);
            lastThrust = thrust;

            ApplyDrag();
        }

        void ApplyDrag(){
            Futz* futz = Futz::Instance();
            float delta = futz->time.delta;

            if (velocity.x > 0)
            {
                velocity.x -= drag.x * delta;
                if (velocity.x < 0)
                {
                    velocity.x = 0;
                }
            }
            else if (velocity.x < 0)
            {
                velocity.x += drag.x * delta;
                if (velocity.x > 0)
                {
                    velocity.x = 0;
                }
            }

            if (velocity.y > 0)
            {
                velocity.y -= drag.y * delta;
                if (velocity.y < 0)
                {
                    velocity.y = 0;
                }
            }
            else if (velocity.y < 0)
            {
                velocity.y += drag.y * delta;
                if (velocity.y > 0)
                {
                    velocity.y = 0;
                }
            }
        }


};
