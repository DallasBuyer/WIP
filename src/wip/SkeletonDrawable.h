#pragma once

#include "spine.h"
#include "extension.h"


class SkeletonDrawable
{
public:
	int x,y;
	bool bmove;
	int s;
	spSkeleton* skeleton;
	spAnimationState* state;
	//ʱ����������
	float time_scale;
	//һ�ֶ�����Ҫ��bounds���ⲿ��ʼ��spineʱ����
	spSkeletonBounds* bounds;

	SkeletonDrawable(spSkeletonData* skeletonData, spAnimationStateData* stateData=0);
	~SkeletonDrawable();
	void UpdateLogic();
	void draw();

	
protected:

private:
	float world_vertices[100];
};
