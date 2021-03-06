#include "InputHandler.h"

void InputHandler::Initialize() {
}

void InputHandler::HandleKeydown(unsigned int key_code) {
	OutputFormatted("Key code: %u", key_code);
	keyboard_down_waiting[key_code] = 1;
	//if (keydown_callback.target != NULL) {
	//	keydown_callback(key_code);
	//}
}

void InputHandler::UpdateStates(int frame_index) {
	prev_keyboard_state = keyboard_state;
	GetKeyboardState(keyboard_state.data());

	if (IsOculusActive()) {
		if (GetKeyPressed('R')) {
			ResetHeadTracking();
		}
		if (GetKeyPressed('L')) {
			ovrHmd_DismissHSWDisplay(oculus->head_mounted_display);
		}
		if (GetKeyToggled('1')) {
			use_predictive = !use_predictive;
			std::cout << "Using prediction: " << use_predictive << std::endl;
		}
		if (GetKeyToggled('9')) {
			predictive_offset_ms -= 1;
			std::cout << "Predictive offset: " << predictive_offset_ms << std::endl;
		}
		if (GetKeyToggled('0')) {
			predictive_offset_ms += 1;
			std::cout << "Predictive offset: " << predictive_offset_ms << std::endl;
		}

		ovrFrameTiming begin_timing = ovrHmd_BeginFrame(oculus->head_mounted_display, frame_index);
		ovrVector3f hmd_to_eye_view_offset[2] = { oculus->eye_rendering_desc[0].HmdToEyeViewOffset, oculus->eye_rendering_desc[1].HmdToEyeViewOffset };
		SetEyeOffsets(hmd_to_eye_view_offset[0], hmd_to_eye_view_offset[1]);

		ovrHmd_GetEyePoses(oculus->head_mounted_display, frame_index, hmd_to_eye_view_offset,
			oculus->eye_rendering_pose, &oculus->tracking_state);
		if (use_predictive) {
			oculus->tracking_state = ovrHmd_GetTrackingState(oculus->head_mounted_display, begin_timing.EyeScanoutSeconds[0]+predictive_offset_ms);
		} else {
			oculus->tracking_state = ovrHmd_GetTrackingState(oculus->head_mounted_display, ovr_GetTimeInSeconds());
		}
	}
}

void InputHandler::ResetHeadTracking() {
	head_pose_center = GetHeadPose().ThePose.Position;
}

bool InputHandler::GetKeyPressed(char key) const {
	return keyboard_state[key] & 0x80;
}

bool InputHandler::GetKeyToggled(char key) const {
	return (keyboard_state[key] & 0x80) && !(prev_keyboard_state[key] & 0x80);
}

ovrPoseStatef InputHandler::GetHeadPose() const {
	return oculus->tracking_state.HeadPose;
}

ovrVector3f InputHandler::GetHeadOffset() const {
	ovrVector3f current_position = GetHeadPose().ThePose.Position;
	return{ current_position.x - head_pose_center.x,
		current_position.y - head_pose_center.y,
		current_position.z - head_pose_center.z };
}

ovrVector3f InputHandler::GetEyeOffset(int eye_number) const {
	//std::array<float, 4> head_orientation = OculusHelper::ConvertQuaternionToArray(GetHeadPose().ThePose.Orientation);
	
	//DirectX::XMVECTOR new_offset = DirectX::XMVector3Transform(
	//	DirectX::XMVectorSet(eye_pose_offsets[eye_number].x, eye_pose_offsets[eye_number].y, eye_pose_offsets[eye_number].z, 1.0f),
	//	DirectX::XMMatrixRotationQuaternion(DirectX::XMVectorSet(head_orientation[0], head_orientation[1], head_orientation[2], head_orientation[3])));
	//ovrVector3f rotated_eye_offset = { DirectX::XMVectorGetX(new_offset) / DirectX::XMVectorGetW(new_offset), DirectX::XMVectorGetY(new_offset) / DirectX::XMVectorGetW(new_offset), DirectX::XMVectorGetZ(new_offset) / DirectX::XMVectorGetW(new_offset) };
	return oculus->eye_rendering_pose[eye_number].Position;
}

ovrVector3f InputHandler::GetActiveEyeOffset() const {
	return GetEyeOffset(active_eye_number);
}

void InputHandler::SetActiveEyeNumber(int eye_number) {
	active_eye_number = eye_number;
}

void InputHandler::SetEyeOffsets(ovrVector3f left_eye_offset, ovrVector3f right_eye_offset) {
	eye_pose_offsets[0] = left_eye_offset;
	eye_pose_offsets[1] = right_eye_offset;
}

void InputHandler::SetOculusState(Oculus* ocu) {
	oculus = ocu;
}

bool InputHandler::IsOculusActive() const {
	return (oculus != NULL);
}