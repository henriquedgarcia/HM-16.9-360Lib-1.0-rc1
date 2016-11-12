This software package is the reference software for Rec. ITU-T H.265 | ISO/IEC 23008-2 High efficiency video coding (HEVC). The reference software includes both encoder and decoder functionality.

Reference software is useful in aiding users of a video coding standard to establish and test conformance and interoperability, and to educate users and demonstrate the capabilities of the standard. For these purposes, this software is provided as an aid for the study and implementation of Rec. ITU-T H.265 | ISO/IEC 23008-2 High efficiency video coding.

The software has been jointly developed by the ITU-T Video Coding Experts Group (VCEG, Question 6 of ITU-T Study Group 16) and the ISO/IEC Moving Picture Experts Group (MPEG, Working Group 11 of Subcommittee 29 of ISO/IEC Joint Technical Committee 1).

A software manual, which contains usage instructions, can be found in the "doc" subdirectory of this software package.

Giving the input 360 test sequence is ERP format, the following command is used to encode the video with different projection format using RA Main10:
(1) encode in ERP domain according to 360 CTC;
./TAppEncoderStatic -c  ./cfg/hm-16.9/encoder_randomaccess_main10_360_ERP.cfg -c ./cfg/per-sequence/360/360test_Train.cfg  -c ./cfg/per-sequence/360/360test_Train_Viewports.cfg  -i ./test_seq/Train_le_8192x4096_60fps_8bit_420_erp.yuv --CodingFaceWidth=4096 --CodingFaceHeight=2048 -f 2 -b test.bin  --SEIDecodedPictureHash=1 -o ''  -q 27
(2) encode in CMP domain according to 360 CTC;
./TAppEncoderStatic -c  ./cfg/hm-16.9/encoder_randomaccess_main10_360_CMP.cfg -c ./cfg/per-sequence/360/360test_Train.cfg  -c ./cfg/per-sequence/360/360test_Train_Viewports.cfg  -i ./test_seq/Train_le_8192x4096_60fps_8bit_420_erp.yuv --CodingFaceWidth=1184 --CodingFaceHeight=1184 -f 2 -b test.bin  --SEIDecodedPictureHash=1 -o ''  -q 27
(3) encode in EAP domain according to 360 CTC;
./TAppEncoderStatic -c  ./cfg/hm-16.9/encoder_randomaccess_main10_360_EAP.cfg -c ./cfg/per-sequence/360/360test_Train.cfg  -c ./cfg/per-sequence/360/360test_Train_Viewports.cfg  -i ./test_seq/Train_le_8192x4096_60fps_8bit_420_erp.yuv --CodingFaceWidth=4096 --CodingFaceHeight=2048 -f 2 -b test.bin  --SEIDecodedPictureHash=1 -o ''  -q 27
(4) encode in OHP domain with frame packing option 1(JVET-D0142) according to 360 CTC;
./TAppEncoderStatic -c  ./cfg/hm-16.9/encoder_randomaccess_main10_360_OHP1.cfg -c ./cfg/per-sequence/360/360test_Train.cfg  -c ./cfg/per-sequence/360/360test_Train_Viewports.cfg  -i ./test_seq/Train_le_8192x4096_60fps_8bit_420_erp.yuv --CodingFaceWidth=1544 --CodingFaceHeight=1336 -f 2 -b test.bin  --SEIDecodedPictureHash=1 -o ''  -q 27
(5) encode in ISP domain with frame packing (JVET-D0028) according to 360 CTC;
./TAppEncoderStatic -c  ./cfg/hm-16.9/encoder_randomaccess_main10_360_CISP.cfg -c ./cfg/per-sequence/360/360test_Train.cfg  -c ./cfg/per-sequence/360/360test_Train_Viewports.cfg  -i ./test_seq/Train_le_8192x4096_60fps_8bit_420_erp.yuv --CodingFaceWidth=952 --CodingFaceHeight=824 -f 2 -b test.bin  --SEIDecodedPictureHash=1 -o ''  -q 27
(6) encode in OHP domain with frame packing option 2(JVET-D0021);
./TAppEncoderStatic -c  ./cfg/hm-16.9/encoder_randomaccess_main10_360_OHP2.cfg -c ./cfg/per-sequence/360/360test_Train.cfg  -c ./cfg/per-sequence/360/360test_Train_Viewports.cfg  -i ./test_seq/Train_le_8192x4096_60fps_8bit_420_erp.yuv --CodingFaceWidth=1544 --CodingFaceHeight=1336 -f 2 -b test.bin  --SEIDecodedPictureHash=1 -o ''  -q 27

For the standalone application TApp360Convert, the example configuration files are in ./cfg/360Lib
./TApp360Convert -c ./cfg/360Lib/360convert_ERP_Cubemap3x2.cfg -c ./cfg/per-sequence/360/360test_Train.cfg -i ./test_seq/Train_le_8192x4096_60fps_8bit_420_erp.yuv -f 1 -o CMP3x2FromERP.yuv 
