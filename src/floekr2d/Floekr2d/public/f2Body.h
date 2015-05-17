#ifndef F2_BODY_H
#define F2_BODY_H

#include <Floekr2d/protected/f2Settings.h>
//#include <Floekr2d/private/f2Vector2.h>
#include <Floekr2d/protected/math/f2Matrix2.h>
#include <Floekr2d/protected/datastruct/f2List.h>

namespace Floekr2d
{
    class f2Shape;

    // --!����Controller�Զ������ײ�������
    namespace core{ class f2ContactController; }

    // --!f2Body��ʵ�ʴ�������ȫ������f2Space�д���allocator��ɵ�
    // --!��������ֶ�new / delete �෴�� �������ܻ�������벻���Ĵ���
    class f2Body
    {
    public:
        enum f2BodyType
        {
            // ����ײ�� �����˶� eg.����
            e_static = 0,
            // ����ײ�� ���˶���
            e_kinematic,
            // ������ײ ���˶���
            e_dynamic
        };

        f2Body();

        void init();

		void setMass(float m)
		{
			mass = m;
		}


		void setInertia(float i)
		{
			inertia = i;
		}

        // setter
        // ��ʼ��������ת����������Ϣ
        void setShape(f2Shape* shape);

        void setPosition(math::f2Vector2f position);

        void setLinearVelocity(math::f2Vector2f linearVelocity);

        void setAngularVelocity(float32 angularVelocity);
        
        // ��תһ������ Ŀǰ����ֱ���趨shape��orient 
        // --!����Ϊ��ת�������ϰ󶨵���״
        void setRadians(float32 radians);

        void setType(f2BodyType type);

        // getter
        // ��õ�ǰ֡�뵱ǰ���巢����ײ�����ж���ָ��
        // --!��������������ݽ����޸� ��ÿ֡����������ϵͳ�����������ô˽��м���
        f2List<f2Body*>& getCollideBodies();

        math::f2Matrix2f getOrient();

        math::f2Vector2f getPosition();

        math::f2Vector2f getLinearVelocity();

        math::f2Vector2f getForces();

        float32 getAngularVelocity();

        float32 getMass();

        float32 getInverseMass();

        float32 getInertia();

        float32 getInverseInertia();

        float32 getRadians();

        float32 getTorque();

        f2Shape* getShape();

        f2BodyType getType();

        // �ṩ�ӿ��ж�body����
        bool isKinematic();

        bool isDynamic();
        
        bool isStatic();

        // ʩ���������
        void applyForce(const math::f2Vector2f& force);
		void applyForce(float32 x,float32 y);


        void applyImpulse(const math::f2Vector2f& impulse, const math::f2Vector2f& contactVector);

        // ������ײ����Զ��������ײ����
        void addCollideBody(f2Body* body);
        
        // ��ײ���� ��ײ���
        // ֧�ֹر���ײ���� / ��ײӦ��
        void setCollisionDetectable(bool detectable);
        
        void setCollisionFeedBack(bool feedback);

        bool isCollisionDetectable();

        bool isCollisionFeedback();

        // ���� ������һ��ѭ��
        void reset();

		// �����ײ����
		void clearCollideList();

        // debug
        void print();

        // ����Ħ��ϵ��
        float32 staticFriction;
        // ���Ħ��ϵ��
        float32 dynamicFriction;

        // ���Իָ�ϵ��
        float32 restitution;

    private:
        // --!��ΪgetCollideBodies()���ص���list������ �ܹ�ֱ�Ӹ�д�ڲ����߼� ��������÷���һ��
        // --!�������Ͳ������װaddCollideBodies()���ڲ���
        //friend core::f2ContactController;

        // ���ٶ� ���ٶ�
        math::f2Vector2f linearVelocity;
        float32 angularVelocity;

        // ���� ת������ ��֮����
        // --!ֱ�Ӵ���body�����������κ�������Ϣ body����Ҳ�����ṩ�κ��趨��������ط���
        // --!����ֻ�ᱻ�趨Ϊ��̬���� mass = inertia = 0.0)
        // --!������ת������һ����Ҫshape�İ󶨲��ܱ��ض�����״��ʼ�� 
        // --!��ֵ���ܶ���� �Ҳ�ͬ����״�����ɵ�������С��������ͬ
        float32 mass, inverseMass;
        float32 inertia, inverseInertia;

        // ��������
        f2BodyType type;

        // ��ײ���״̬
        // --!���ر�����ײ�����ôҲ���Զ��ر���ײ����
        bool collisionDetectable;
        // ������״̬
        bool collisionFeedback;

        // ���屻ʩ�ӵĺ����������
        math::f2Vector2f force;
        float32 torque;

        // ��ǰ֡�뵱ǰ��������ײ����ײ�������
        f2List<f2Body*> collideBodies;

        f2Shape *shape;
    };
}

#endif