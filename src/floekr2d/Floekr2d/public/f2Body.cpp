#include <Floekr2d/public/f2Body.h>
#include <Floekr2d/public/shape/f2Shape.h>

namespace Floekr2d
{
    f2Body::f2Body()
    {
        init();
    }

    void f2Body::init()
    {
        linearVelocity.zero();
        angularVelocity = 0.0f;

        restitution = 0.2f;
        staticFriction = 0.5f;
        dynamicFriction = 0.3f;

        mass = 0.0f;
        inverseMass = 0.0f;
        inertia = 0.0f;
        inverseInertia = 0.0f;

        // Ĭ�����е����嶼�ǿ���ײ��
        type = e_kinematic;

        force.zero();
        torque = 0.0f;

        shape = NULL;

        collisionDetectable = true;
        collisionFeedback = true;
    }

    // ��ʼ��������ת����������Ϣ
    void f2Body::setShape(f2Shape* shape)
    {
        // �ų�0��Ϊ��ĸ�����
        f2MassData massData = shape->computeMass();

        // ��̬��������Ϊ0
        if(type == e_static)
        {
            massData.mass = 0.0f;
            massData.inertia = 0.0f;
        }

        mass = massData.mass;
        inverseMass = mass ? 1.0f / mass : 0.0f;

        inertia = massData.inertia;
        inverseInertia = inertia ? 1.0f / inertia : 0.0f;

        if(mass == 0.0f || inverseMass == 0.0f)
            //�Զ�����Ϊstatic����
            type = e_static;

        this->shape = shape;
    }

    //void f2Body::setOrient(float32 radians)
    //{

    //}

    void f2Body::setPosition(math::f2Vector2f position)
    {
        if(shape == NULL)
        {
#ifdef _DEBUG
            //std::cout << "shapeΪ�� ����setShape()�������趨ֵ" << std::endl;
            f2Log("shapeΪ�� ����setShape()�������趨ֵ\n");
#endif
            return;
        }

        shape->setPosition(position);
    }

    void f2Body::setLinearVelocity(math::f2Vector2f linearVelocity)
    {
        this->linearVelocity = linearVelocity;
    }

    void f2Body::setAngularVelocity(float32 angularVelocity)
    {
        this->angularVelocity = angularVelocity;
    }

    // ��תһ������
    // --!����Ϊ��ת�������ϰ󶨵���״
    void f2Body::setRadians(float32 radians)
    {
        if(shape == NULL)
        {
#ifdef _DEBUG
            //std::cout << "shapeΪ�� ����setShape()�������趨ֵΪ" << radians << "���ȵĳ���" << std::endl;
            f2Log("shapeΪ�� ����setShape()�������趨ֵΪ%f���ȵĳ���\n");
#endif
            return;
        }

        shape->setOrient(radians);
    }

    void f2Body::setType(f2BodyType type)
    {
        this->type = type;
    }

    // getter
    math::f2Matrix2f f2Body::getOrient()
    {
        return shape->getOrient();
    }

    math::f2Vector2f f2Body::getPosition()
    {
        return shape->getPosition();
    }

    math::f2Vector2f f2Body::getLinearVelocity()
    {
        return linearVelocity;
    }

    math::f2Vector2f f2Body::getForces()
    {
        return force;
    }

    float32 f2Body::getAngularVelocity()
    {
        return angularVelocity;
    }

    float32 f2Body::getMass()
    {
        return mass;
    }

    float32 f2Body::getInverseMass()
    {
        return inverseMass;
    }

    float32 f2Body::getInertia()
    {
        return inertia;
    }

    float32 f2Body::getInverseInertia()
    {
        return inverseInertia;
    }

    //float32 f2Body::getRestitution()
    //{
    //    return restitution;
    //}

    float32 f2Body::getRadians()
    {
        return shape->getRadians();
    }

    float32 f2Body::getTorque()
    {
        return torque;
    }

    f2Shape* f2Body::getShape()
    {
        if(shape == NULL)
        {
#ifdef _DEBUG
            f2Log("shape == NULL �м����ⲿʹ�ô�ָ��\n");
#endif
        }
        return shape;
    }

    f2List<f2Body*>& f2Body::getCollideBodies()
    {
        return collideBodies;
    }

    f2Body::f2BodyType f2Body::getType()
    {
        return type;
    }

    // ʩ���������
    void f2Body::applyForce(const math::f2Vector2f& force)
    {
        this->force += force;
    }

	void f2Body::applyForce(float32 x,float32 y)
	{
		math::f2Vector2f f(x,y);
		this->force += f;
	}

    void f2Body::applyImpulse(const math::f2Vector2f& impulse, const math::f2Vector2f& contactVector)
    {
        linearVelocity += inverseMass * impulse;
        angularVelocity += inverseInertia * contactVector.cross(impulse);
    }

    void f2Body::reset()
    {
        force.set(0, 0);
        torque = 0.0f;
    }

	void f2Body::clearCollideList()
	{
        // �����ײ����
        collideBodies.clear();
	}

    void f2Body::print()
    {
#ifdef _DEBUG
        // ���ٶ� ���ٶ�
        linearVelocity.print("linearVelocity");

        std::cout << "angularVelocity:" << angularVelocity << std::endl << std::endl;

        // λ��
        shape->getPosition().print("position");

        // ����Ħ�� ���Ħ��
        std::cout << "staticFriction:" << staticFriction << std::endl;
        std::cout << "dynamicFriction:" << dynamicFriction << std::endl << std::endl;

        std::cout << "restitution:" << restitution << std::endl << std::endl;

        // ���� ת������ ��֮����
        // --!ֱ�Ӵ���body�����������κ�������Ϣ body����Ҳ�����ṩ�κ��趨��������ط���
        // --!����ֻ�ᱻ�趨Ϊ��̬���� mass = inertia = 0.0)
        // --!������ת������һ����Ҫshape�İ󶨲��ܱ��ض�����״��ʼ�� 
        // --!��ֵ���ܶ���� �Ҳ�ͬ����״�����ɵ�������С��������ͬ
        std::cout << "inverseMass:" << inverseMass << std::endl;
        std::cout << "mass:" << mass << std::endl;
        std::cout << "inertia:" << inertia << std::endl;
        std::cout << "inverseInertia:" << inverseInertia << std::endl << std::endl;

        // ���屻ʩ�ӵĺ����������
        force.print("force");
        std::cout << "torque:" << torque << std::endl;
#endif
    }

    void f2Body::addCollideBody(f2Body* body)
    {
        collideBodies.pushback(body);
    }

    bool f2Body::isKinematic()
    {
        return type == e_kinematic;
    }

    bool f2Body::isDynamic()
    {
        return type == e_dynamic;
    }

    bool f2Body::isStatic()
    {
        return type == e_static;
    }

    void f2Body::setCollisionDetectable(bool detectable)
    {
        if(!detectable)
            collisionFeedback = false;

        this->collisionDetectable = detectable;
    }

    void f2Body::setCollisionFeedBack(bool feedback)
    {
        this->collisionFeedback = feedback;
    }

    bool f2Body::isCollisionDetectable()
    {
        return collisionDetectable;
    }

    bool f2Body::isCollisionFeedback()
    {
        return collisionFeedback;
    }

}
