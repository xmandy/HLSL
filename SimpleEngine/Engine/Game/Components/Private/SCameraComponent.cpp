#include "Public/SCameraComponent.h"

using namespace std;
using namespace DirectX;

namespace SEngine
{
SRTTI_DEFINITIONS(SCamera)

SCamera::SCamera(SGame& game, float nearPlaneDistance, float farPlaneDistance) :
	SGameComponent(game),
	mNearPlaneDistance(nearPlaneDistance), mFarPlaneDistance(farPlaneDistance)
{
}

const XMFLOAT3& SCamera::Position() const
{
	return mPosition;
}

const XMFLOAT3& SCamera::Direction() const
{
	return mDirection;
}

const XMFLOAT3& SCamera::Up() const
{
	return mUp;
}

const XMFLOAT3& SCamera::Right() const
{
	return mRight;
}

XMVECTOR SCamera::PositionVector() const
{
	return XMLoadFloat3(&mPosition);
}

XMVECTOR SCamera::DirectionVector() const
{
	return XMLoadFloat3(&mDirection);
}

XMVECTOR SCamera::UpVector() const
{
	return XMLoadFloat3(&mUp);
}

XMVECTOR SCamera::RightVector() const
{
	return XMLoadFloat3(&mRight);
}

float SCamera::NearPlaneDistance() const
{
	return mNearPlaneDistance;
}

void SCamera::SetNearPlaneDistance(float distance)
{
	mNearPlaneDistance = distance;
	mProjectionMatrixDataDirty = true;
}

float SCamera::FarPlaneDistance() const
{
	return mFarPlaneDistance;
}

void SCamera::SetFarPlaneDistance(float distance)
{
	mFarPlaneDistance = distance;
	mProjectionMatrixDataDirty = true;
}

XMMATRIX SCamera::ViewMatrix() const
{
	return XMLoadFloat4x4(&mViewMatrix);
}

XMMATRIX SCamera::ProjectionMatrix() const
{
	return XMLoadFloat4x4(&mProjectionMatrix);
}

XMMATRIX SCamera::ViewProjectionMatrix() const
{
	XMMATRIX viewMatrix = XMLoadFloat4x4(&mViewMatrix);
	XMMATRIX projectionMatrix = XMLoadFloat4x4(&mProjectionMatrix);

	return XMMatrixMultiply(viewMatrix, projectionMatrix);
}

const vector<function<void()>>& SCamera::ViewMatrixUpdatedCallbacks() const
{
	return mViewMatrixUpdatedCallbacks;
}

void SCamera::AddViewMatrixUpdatedCallback(function<void()> callback)
{
	mViewMatrixUpdatedCallbacks.push_back(callback);
}

const vector<function<void()>>& SCamera::ProjectionMatrixUpdatedCallbacks() const
{
	return mProjectionMatrixUpdatedCallbacks;
}

void SCamera::AddProjectionMatrixUpdatedCallback(function<void()> callback)
{
	mProjectionMatrixUpdatedCallbacks.push_back(callback);
}

void SCamera::SetPosition(float x, float y, float z)
{
	XMVECTOR position = XMVectorSet(x, y, z, 1.0f);
	SetPosition(position);
}

void SCamera::SetPosition(FXMVECTOR position)
{
	XMStoreFloat3(&mPosition, position);
	mViewMatrixDataDirty = true;
}

void SCamera::SetPosition(const XMFLOAT3& position)
{
	mPosition = position;
	mViewMatrixDataDirty = true;
}

void SCamera::Reset()
{
	mPosition = Vector3Helper::Zero;
	mDirection = Vector3Helper::Forward;
	mUp = Vector3Helper::Up;
	mRight = Vector3Helper::Right;
	mViewMatrixDataDirty = true;

	UpdateViewMatrix();
}

void SCamera::Initialize()
{
	UpdateProjectionMatrix();
	Reset();
}

void SCamera::Update(const SGameTime&)
{
	if (mViewMatrixDataDirty)
	{
		UpdateViewMatrix();
	}
}

void SCamera::UpdateViewMatrix()
{
	XMVECTOR eyePosition = XMLoadFloat3(&mPosition);
	XMVECTOR direction = XMLoadFloat3(&mDirection);
	XMVECTOR upDirection = XMLoadFloat3(&mUp);

	XMMATRIX viewMatrix = XMMatrixLookToRH(eyePosition, direction, upDirection);
	XMStoreFloat4x4(&mViewMatrix, viewMatrix);

	for (auto& callback : mViewMatrixUpdatedCallbacks)
	{
		callback();
	}

	mViewMatrixDataDirty = false;
}

void SCamera::ApplyRotation(CXMMATRIX transform)
{
	XMVECTOR direction = XMLoadFloat3(&mDirection);
	XMVECTOR up = XMLoadFloat3(&mUp);

	direction = XMVector3TransformNormal(direction, transform);
	direction = XMVector3Normalize(direction);

	up = XMVector3TransformNormal(up, transform);
	up = XMVector3Normalize(up);

	XMVECTOR right = XMVector3Cross(direction, up);
	up = XMVector3Cross(right, direction);

	XMStoreFloat3(&mDirection, direction);
	XMStoreFloat3(&mUp, up);
	XMStoreFloat3(&mRight, right);

	mViewMatrixDataDirty = true;
}

void SCamera::ApplyRotation(const XMFLOAT4X4& transform)
{
	XMMATRIX transformMatrix = XMLoadFloat4x4(&transform);
	ApplyRotation(transformMatrix);
}
}
