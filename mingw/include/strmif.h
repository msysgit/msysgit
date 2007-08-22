#ifndef _STRMIF_H
#define _STRMIF_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - DirectShow Enumerated Types - TVAudioMode Enumeration */
#define TVAUDIO_MODE_MASK 0x000000FF
#define TVAUDIO_PRESET_MASK 0x0000FF00
/*--- DirectShow Reference - DirectShow Data Types */
typedef LONGLONG REFERENCE_TIME;
typedef double REFTIME;
/*--- DirectShow Reference - Constants and GUIDs */
enum { 
	MERIT_PREFERRED = 0x800000,
	MERIT_NORMAL = 0x600000,
	MERIT_UNLIKELY = 0x400000,
	MERIT_DO_NOT_USE = 0x200000,
	MERIT_SW_COMPRESSOR = 0x100000,
	MERIT_HW_COMPRESSOR = 0x100050
};
/*--- DirectShow Reference - DirectShow Enumerated Types */
typedef enum _AM_AUDIO_RENDERER_STAT_PARAM {
	AM_AUDREND_STAT_PARAM_BREAK_COUNT = 1,
	AM_AUDREND_STAT_PARAM_SLAVE_MODE,
	AM_AUDREND_STAT_PARAM_SILENCE_DUR,
	AM_AUDREND_STAT_PARAM_LAST_BUFFER_DUR,
	AM_AUDREND_STAT_PARAM_DISCONTINUITIES,
	AM_AUDREND_STAT_PARAM_SLAVE_RATE,
	AM_AUDREND_STAT_PARAM_SLAVE_DROPWRITE_DUR,
	AM_AUDREND_STAT_PARAM_SLAVE_HIGHLOWERROR,
	AM_AUDREND_STAT_PARAM_SLAVE_LASTHIGHLOWERROR,
	AM_AUDREND_STAT_PARAM_SLAVE_ACCUMERROR,
	AM_AUDREND_STAT_PARAM_BUFFERFULLNESS,
	AM_AUDREND_STAT_PARAM_JITTER
} AM_AUDIO_RENDERER_STAT_PARAM;
typedef enum _AM_DVD_GRAPH_FLAGS {
	AM_DVD_HWDEC_PREFER = 0x01,
	AM_DVD_HWDEC_ONLY = 0x02,
	AM_DVD_SWDEC_PREFER = 0x04,
	AM_DVD_SWDEC_ONLY = 0x08,
	AM_DVD_NOVPE = 0x100,
	AM_DVD_VMR9_ONLY = 0x800,
	AM_DVD_EVR_ONLY = 0x1000
} AM_DVD_GRAPH_FLAGS;
typedef enum _AM_DVD_STREAM_FLAGS {
	AM_DVD_STREAM_VIDEO = 0x01,
	AM_DVD_STREAM_AUDIO = 0x02,
	AM_DVD_STREAM_SUBPIC = 0x04
} AM_DVD_STREAM_FLAGS;
typedef enum _AM_FILTER_MISC_FLAGS {
	AM_FILTER_MISC_FLAGS_IS_RENDERER = 0x00000001,
	AM_FILTER_MISC_FLAGS_IS_SOURCE = 0x00000002
} AM_FILTER_MISC_FLAGS;
typedef enum _AM_GRAPH_CONFIG_RECONNECT_FLAGS {
	AM_GRAPH_CONFIG_RECONNECT_DIRECTCONNECT = 0x00000001,
	AM_GRAPH_CONFIG_RECONNECT_CACHE_REMOVED_FILTERS = 0x00000002,
	AM_GRAPH_CONFIG_RECONNECT_USE_ONLY_CACHED_FILTERS = 0x00000004
} AM_GRAPH_CONFIG_RECONNECT_FLAGS;
typedef enum _AM_INTF_SEARCH_FLAGS {
	AM_INTF_SEARCH_INPUT_PIN = 0x00000001,
	AM_INTF_SEARCH_OUTPUT_PIN = 0x00000002,
	AM_INTF_SEARCH_FILTER = 0x00000004
} AM_INTF_SEARCH_FLAGS;
typedef enum _AM_OVERLAY_NOTIFY_FLAGS {
	AM_OVERLAY_NOTIFY_VISIBLE_CHANGE = 0x00000001,
	AM_OVERLAY_NOTIFY_SOURCE_CHANGE = 0x00000002,
	AM_OVERLAY_NOTIFY_DEST_CHANGE = 0x00000004
} AM_OVERLAY_NOTIFY_FLAGS;
typedef enum _AM_PIN_CONNECTION_BLOCK_FLAGS {
	AM_PIN_FLOW_CONTROL_BLOCK = 0x00000001,
	AM_PIN_PUSH_THROUGH_DATA = 0x00000002
} AM_PIN_CONNECTION_BLOCK_FLAGS;
typedef enum _AM_PUSHSOURCE_FLAGS {
	AM_PUSHSOURCECAPS_INTERNAL_RM = 0x00000001,
	AM_PUSHSOURCECAPS_NOT_LIVE = 0x00000002,
	AM_PUSHSOURCECAPS_PRIVATE_CLOCK = 0x00000004,
	AM_PUSHSOURCEREQS_USE_STREAM_CLOCK = 0x00010000
} AM_PUSHSOURCE_FLAGS;
typedef enum tagAM_SAMPLE_PROPERTY_FLAGS {
	AM_SAMPLE_SPLICEPOINT = 0x01,
	AM_SAMPLE_PREROLL = 0x02,
	AM_SAMPLE_DATADISCONTINUITY = 0x04,
	AM_SAMPLE_TYPECHANGED = 0x08,
	AM_SAMPLE_TIMEVALID = 0x10,
	AM_SAMPLE_TIMEDISCONTINUITY = 0x40,
	AM_SAMPLE_FLUSH_ON_PAUSE = 0x80,
	AM_SAMPLE_STOPVALID = 0x100,
	AM_SAMPLE_ENDOFSTREAM = 0x200,
	AM_STREAM_MEDIA = 0,
	AM_STREAM_CONTROL = 1
} AM_SAMPLE_PROPERTY_FLAGS;
typedef enum AM_SEEKING_SeekingCapabilities {
	AM_SEEKING_CanSeekAbsolute = 0x1,
	AM_SEEKING_CanSeekForwards = 0x2,
	AM_SEEKING_CanSeekBackwards = 0x4,
	AM_SEEKING_CanGetCurrentPos = 0x8,
	AM_SEEKING_CanGetStopPos = 0x10,
	AM_SEEKING_CanGetDuration = 0x20,
	AM_SEEKING_CanPlayBackwards = 0x40,
	AM_SEEKING_CanDoSegments = 0x80,
	AM_SEEKING_Source = 0x100
} AM_SEEKING_SEEKING_CAPABILITIES;
typedef enum {
	AM_STREAM_INFO_START_DEFINED = 0x00000001,
	AM_STREAM_INFO_STOP_DEFINED = 0x00000002,
	AM_STREAM_INFO_DISCARDING = 0x00000004,
	AM_STREAM_INFO_STOP_SEND_EXTRA = 0x00000010
} AM_STREAM_INFO_FLAGS;
enum AMOVERLAYFX {
	AMOVERFX_NOFX = 0x00000000,
	AMOVERFX_MIRRORLEFTRIGHT = 0x00000002,
	AMOVERFX_MIRRORUPDOWN = 0x00000004,
	AMOVERFX_DEINTERLACE = 0x00000008
};
typedef enum _AMRESCTL_RESERVEFLAGS {
	AMRESCTL_RESERVEFLAGS_RESERVE = 0x00,
	AMRESCTL_RESERVEFLAGS_UNRESERVE = 0x01
} AMRESCTL_RESERVEFLAGS;
typedef enum tagAMTunerModeType {
	AMTUNER_MODE_DEFAULT = 0x0000,
	AMTUNER_MODE_TV = 0x0001,
	AMTUNER_MODE_FM_RADIO = 0x0002,
	AMTUNER_MODE_AM_RADIO = 0x0004,
	AMTUNER_MODE_DSS = 0x0008
} AMTunerModeType;
typedef enum tagAnalogVideoStandard {
	AnalogVideo_None = 0x00000000,
	AnalogVideo_NTSC_M = 0x00000001,
	AnalogVideo_NTSC_M_J = 0x00000002,
	AnalogVideo_NTSC_433 = 0x00000004,
	AnalogVideo_PAL_B = 0x00000010,
	AnalogVideo_PAL_D = 0x00000020,
	AnalogVideo_PAL_H = 0x00000080,
	AnalogVideo_PAL_I = 0x00000100,
	AnalogVideo_PAL_M = 0x00000200,
	AnalogVideo_PAL_N = 0x00000400,
	AnalogVideo_PAL_60 = 0x00000800,
	AnalogVideo_SECAM_B = 0x00001000,
	AnalogVideo_SECAM_D = 0x00002000,
	AnalogVideo_SECAM_G = 0x00004000,
	AnalogVideo_SECAM_H = 0x00008000,
	AnalogVideo_SECAM_K = 0x00010000,
	AnalogVideo_SECAM_K1 = 0x00020000,
	AnalogVideo_SECAM_L = 0x00040000,
	AnalogVideo_SECAM_L1 = 0x00080000,
	AnalogVideo_PAL_N_COMBO = 0x00100000
} AnalogVideoStandard;
typedef enum {
	CameraControl_Flags_Auto = 0x0001,
	CameraControl_Flags_Manual = 0x0002
} CameraControlFlags;
typedef enum {
	CameraControl_Pan = 1,
	CameraControl_Tilt,
	CameraControl_Roll,
	CameraControl_Zoom,
	CameraControl_Exposure,
	CameraControl_Iris,
	CameraControl_Focus
} CameraControlProperty;
typedef enum {
	CompressionCaps_CanQuality = 0x01,
	CompressionCaps_CanCrunch = 0x02,
	CompressionCaps_CanKeyFrame = 0x04,
	CompressionCaps_CanBFrame = 0x08,
	CompressionCaps_CanWindow = 0x10
} CompressionCaps;
typedef enum {
	DECIMATION_LEGACY,
	DECIMATION_USE_DECODER_ONLY,
	DECIMATION_USE_VIDEOPORT_ONLY,
	DECIMATION_USE_OVERLAY_ONLY,
	DECIMATION_DEFAULT
} DECIMATION_USAGE;
typedef enum tagDVD_AUDIO_APPMODE {
	DVD_AudioMode_None = 0,
	DVD_AudioMode_Karaoke = 1,
	DVD_AudioMode_Surround = 2,
	DVD_AudioMode_Other = 3
} DVD_AUDIO_APPMODE;
typedef enum tagDVD_AUDIO_FORMAT {
	DVD_AudioFormat_AC3 = 0,
	DVD_AudioFormat_MPEG1 = 1,
	DVD_AudioFormat_MPEG1_DRC = 2,
	DVD_AudioFormat_MPEG2 = 3,
	DVD_AudioFormat_MPEG2_DRC = 4,
	DVD_AudioFormat_LPCM = 5,
	DVD_AudioFormat_DTS = 6,
	DVD_AudioFormat_SDDS = 7,
	DVD_AudioFormat_Other = 8
} DVD_AUDIO_FORMAT;
typedef enum tagDVD_AUDIO_LANG_EXT {
	DVD_AUD_EXT_NotSpecified = 0,
	DVD_AUD_EXT_Captions = 1,
	DVD_AUD_EXT_VisuallyImpaired = 2,
	DVD_AUD_EXT_DirectorComments1 = 3,
	DVD_AUD_EXT_DirectorComments2 = 4
} DVD_AUDIO_LANG_EXT;
typedef enum {
	DVD_CMD_FLAG_None = 0x00000000,
	DVD_CMD_FLAG_Flush = 0x00000001,
	DVD_CMD_FLAG_SendEvents = 0x00000002,
	DVD_CMD_FLAG_Block = 0x00000004,
	DVD_CMD_FLAG_StartWhenRendered = 0x00000008,
	DVD_CMD_FLAG_EndAfterRendered = 0x00000010
} DVD_CMD_FLAGS;
typedef enum tagDVD_DISC_SIDE {
	DVD_SIDE_A,
	DVD_SIDE_B
} DVD_DISC_SIDE;
typedef enum tagDVD_DOMAIN {
	DVD_DOMAIN_FirstPlay,
	DVD_DOMAIN_VideoManagerMenu,
	DVD_DOMAIN_VideoTitleSetMenu,
	DVD_DOMAIN_Title,
	DVD_DOMAIN_Stop
} DVD_DOMAIN;
typedef enum tagDVD_FRAMERATE {
	DVD_FPS_25 = 1,
	DVD_FPS_30NonDrop = 3
} DVD_FRAMERATE;
typedef enum tagDVD_KARAOKE_ASSIGNMENT {
	DVD_Assignment_reserved0 = 0,
	DVD_Assignment_reserved1 = 1,
	DVD_Assignment_LR = 2,
	DVD_Assignment_LRM = 3,
	DVD_Assignment_LR1 = 4,
	DVD_Assignment_LRM1 = 5,
	DVD_Assignment_LR12 = 6,
	DVD_Assignment_LRM12 = 7 
} DVD_KARAOKE_ASSIGNMENT;
typedef enum tagDVD_KARAOKE_CONTENTS {
	DVD_Karaoke_GuideVocal1 = 0x0001,
	DVD_Karaoke_GuideVocal2 = 0x0002,
	DVD_Karaoke_GuideMelody1 = 0x0004,
	DVD_Karaoke_GuideMelody2 = 0x0008,
	DVD_Karaoke_GuideMelodyA = 0x0010,
	DVD_Karaoke_GuideMelodyB = 0x0020,
	DVD_Karaoke_SoundEffectA = 0x0040,
	DVD_Karaoke_SoundEffectB = 0x0080
} DVD_KARAOKE_CONTENTS;
typedef enum tagDVD_KARAOKE_DOWNMIX {
	DVD_Mix_0to0 = 0x0001,
	DVD_Mix_1to0 = 0x0002,
	DVD_Mix_2to0 = 0x0004,
	DVD_Mix_3to0 = 0x0008,
	DVD_Mix_4to0 = 0x0010,
	DVD_Mix_Lto0 = 0x0020,
	DVD_Mix_Rto0 = 0x0040,
	DVD_Mix_0to1 = 0x0100,
	DVD_Mix_1to1 = 0x0200,
	DVD_Mix_2to1 = 0x0400,
	DVD_Mix_3to1 = 0x0800,
	DVD_Mix_4to1 = 0x1000,
	DVD_Mix_Lto1 = 0x2000,
	DVD_Mix_Rto1 = 0x4000
} DVD_KARAOKE_DOWNMIX;
typedef enum tagDVD_MENU_ID {
	DVD_MENU_Title = 2,
	DVD_MENU_Root = 3,
	DVD_MENU_Subpicture = 4,
	DVD_MENU_Audio = 5,
	DVD_MENU_Angle = 6,
	DVD_MENU_Chapter = 7
} DVD_MENU_ID;
typedef enum {
	DVD_ResetOnStop = 1,
	DVD_NotifyParentalLevelChange = 2,
	DVD_HMSF_TimeCodeEvents = 3,
	DVD_AudioDuringFFwdRew = 4,
	DVD_EnableNonblockingAPIs = 5,
	DVD_CacheSizeInMB = 6,
	DVD_EnablePortableBookmarks = 7
} DVD_OPTION_FLAG;
typedef enum tagDVD_PARENTAL_LEVEL {
	DVD_PARENTAL_LEVEL_8 = 0x8000,
	DVD_PARENTAL_LEVEL_7 = 0x4000,
	DVD_PARENTAL_LEVEL_6 = 0x2000,
	DVD_PARENTAL_LEVEL_5 = 0x1000,
	DVD_PARENTAL_LEVEL_4 = 0x0800,
	DVD_PARENTAL_LEVEL_3 = 0x0400,
	DVD_PARENTAL_LEVEL_2 = 0x0200,
	DVD_PARENTAL_LEVEL_1 = 0x0100
} DVD_PARENTAL_LEVEL;
typedef enum tagDVD_PREFERRED_DISPLAY_MODE {
	DISPLAY_CONTENT_DEFAULT = 0,
	DISPLAY_16x9 = 1,
	DISPLAY_4x3_PANSCAN_PREFERRED = 2,
	DISPLAY_4x3_LETTERBOX_PREFERRED = 3
} DVD_PREFERRED_DISPLAY_MODE;
typedef enum tagDVD_RELATIVE_BUTTON {
	DVD_Relative_Upper = 1,
	DVD_Relative_Lower = 2,
	DVD_Relative_Left = 3,
	DVD_Relative_Right = 4
} DVD_RELATIVE_BUTTON;
typedef enum tagDVD_SUBPICTURE_LANG_EXT {
	DVD_SP_EXT_NotSpecified = 0,
	DVD_SP_EXT_Caption_Normal = 1,
	DVD_SP_EXT_Caption_Big = 2,
	DVD_SP_EXT_Caption_Children = 3,
	DVD_SP_EXT_CC_Normal = 5,
	DVD_SP_EXT_CC_Big = 6,
	DVD_SP_EXT_CC_Children = 7,
	DVD_SP_EXT_Forced = 9,
	DVD_SP_EXT_DirectorComments_Normal = 13,
	DVD_SP_EXT_DirectorComments_Big = 14,
	DVD_SP_EXT_DirectorComments_Children = 15
} DVD_SUBPICTURE_LANG_EXT;
typedef enum tagDVD_SUBPICTURE_TYPE {
	DVD_SPType_NotSpecified = 0,
	DVD_SPType_Language = 1,
	DVD_SPType_Other = 2
} DVD_SUBPICTURE_TYPE;
typedef enum tagDVD_SUBPICTURE_CODING {
	DVD_SPCoding_RunLength = 0,
	DVD_SPCoding_Extended = 1,
	DVD_SPCoding_Other = 2
} DVD_SUBPICTURE_CODING;
enum DVD_TextCharSet {
	DVD_CharSet_Unicode = 0,
	DVD_CharSet_ISO646 = 1,
	DVD_CharSet_JIS_Roman_Kanji = 2,
	DVD_CharSet_ISO8859_1 = 3,
	DVD_CharSet_ShiftJIS_Kanji_Roman_Katakana = 4
};
enum DVD_TextStringType {
	DVD_Struct_Volume = 0x01,
	DVD_Struct_Title = 0x02,
	DVD_Struct_ParentalID = 0x03,
	DVD_Struct_PartOfTitle = 0x04,
	DVD_Struct_Cell = 0x05,
	DVD_Stream_Audio = 0x10,
	DVD_Stream_Subpicture = 0x11,
	DVD_Stream_Angle = 0x12,
	DVD_Channel_Audio = 0x20,
	DVD_General_Name = 0x30,
	DVD_General_Comments = 0x31,
	DVD_Title_Series = 0x38,
	DVD_Title_Movie = 0x39,
	DVD_Title_Video = 0x3a,
	DVD_Title_Album = 0x3b,
	DVD_Title_Song = 0x3c,
	DVD_Title_Other = 0x3f,
	DVD_Title_Sub_Series = 0x40,
	DVD_Title_Sub_Movie = 0x41,
	DVD_Title_Sub_Video = 0x42,
	DVD_Title_Sub_Album = 0x43,
	DVD_Title_Sub_Song = 0x44,
	DVD_Title_Sub_Other = 0x47,
	DVD_Title_Orig_Series = 0x48,
	DVD_Title_Orig_Movie = 0x49,
	DVD_Title_Orig_Video = 0x4a,
	DVD_Title_Orig_Album = 0x4b,
	DVD_Title_Orig_Song = 0x4c,
	DVD_Title_Orig_Other = 0x4f,
	DVD_Other_Scene = 0x50,
	DVD_Other_Cut = 0x51,
	DVD_Other_Take = 0x52
};
typedef enum tagDVD_TIMECODE_FLAGS {
	DVD_TC_FLAG_25fps = 0x00000001,
	DVD_TC_FLAG_30fps = 0x00000002,
	DVD_TC_FLAG_DropFrame = 0x00000004,
	DVD_TC_FLAG_Interpolated = 0x00000008
} DVD_TIMECODE_FLAGS;
typedef enum tagDVD_TITLE_APPMODE {
	DVD_AppMode_Not_Specified = 0,
	DVD_AppMode_Karaoke = 1,
	DVD_AppMode_Other = 3 
} DVD_TITLE_APPMODE;
typedef enum tagDVD_VIDEO_COMPRESSION {
	DVD_VideoCompression_Other = 0,
	DVD_VideoCompression_MPEG1 = 1,
	DVD_VideoCompression_MPEG2 = 2 
} DVD_VIDEO_COMPRESSION;
typedef enum _DVDECODERRESOLUTION {
	DVDECODERRESOLUTION_720x480 = 1000,
	DVDECODERRESOLUTION_360x240 = 1001,
	DVDECODERRESOLUTION_180x120 = 1002,
	DVDECODERRESOLUTION_88x60 = 1003
} DVDECODERRESOLUTION;
typedef enum _DVRESOLUTION {
	DVRESOLUTION_FULL = 1000,
	DVRESOLUTION_HALF = 1001,
	DVRESOLUTION_QUARTER = 1002,
	DVRESOLUTION_DC = 1003
} DVRESOLUTION;
typedef enum _DVENCODERFORMAT {
	DVENCODERFORMAT_DVSD = 2007,
	DVENCODERFORMAT_DVHD = 2008,
	DVENCODERFORMAT_DVSL = 2009
} DVENCODERFORMAT;
typedef enum _DVENCODERRESOLUTION {
	DVENCODERRESOLUTION_720x480 = 2012,
	DVENCODERRESOLUTION_360x240 = 2013,
	DVENCODERRESOLUTION_180x120 = 2014,
	DVENCODERRESOLUTION_88x60 = 2015
} DVENCODERRESOLUTION;
typedef enum _DVENCODERVIDEOFORMAT {
	DVENCODERVIDEOFORMAT_NTSC = 2000,
	DVENCODERVIDEOFORMAT_PAL = 2001
} DVENCODERVIDEOFORMAT;
typedef enum _FilterState {
	State_Stopped,
	State_Paused,
	State_Running
} FILTER_STATE;
typedef enum {
	INTERLEAVE_NONE,
	INTERLEAVE_CAPTURE,
	INTERLEAVE_FULL,
	INTERLEAVE_NONE_BUFFERED
} InterleavingMode;
typedef enum {
	PhysConn_Video_Tuner = 1,
	PhysConn_Video_Composite,
	PhysConn_Video_SVideo,
	PhysConn_Video_RGB,
	PhysConn_Video_YRYBY,
	PhysConn_Video_SerialDigital,
	PhysConn_Video_ParallelDigital,
	PhysConn_Video_SCSI,
	PhysConn_Video_AUX,
	PhysConn_Video_1394,
	PhysConn_Video_USB,
	PhysConn_Video_VideoDecoder,
	PhysConn_Video_VideoEncoder,
	PhysConn_Video_SCART,
	PhysConn_Video_Black,
	PhysConn_Audio_Tuner = 4096,
	PhysConn_Audio_Line,
	PhysConn_Audio_Mic,
	PhysConn_Audio_AESDigital,
	PhysConn_Audio_SPDIFDigital,
	PhysConn_Audio_SCSI,
	PhysConn_Audio_AUX,
	PhysConn_Audio_1394,
	PhysConn_Audio_USB,
	PhysConn_Audio_AudioDecoder
} PhysicalConnectorType;
typedef enum _PinDirection {
	PINDIR_INPUT,
	PINDIR_OUTPUT
} PIN_DIRECTION;
typedef enum {
	Famine,
	Flood
} QualityMessageType;
enum {
	REG_PINFLAG_B_ZERO = 0x1,
	REG_PINFLAG_B_RENDERER = 0x2,
	REG_PINFLAG_B_MANY = 0x4,
	REG_PINFLAG_B_OUTPUT = 0x8
} REG_PINFLAG;
typedef enum _REM_FILTER_FLAGS {
	REMFILTERF_LEAVECONNECTED = 0x00000001
} REM_FILTER_FLAGS;
typedef enum {
	TunerInputCable,
	TunerInputAntenna
} TunerInputType;
typedef enum tagTVAudioMode {
	AMTVAUDIO_MODE_MONO = 0x0001,
	AMTVAUDIO_MODE_STEREO = 0x0002,
	AMTVAUDIO_MODE_LANG_A = 0x0010,
	AMTVAUDIO_MODE_LANG_B = 0x0020,
	AMTVAUDIO_MODE_LANG_C = 0x0040,
	AMTVAUDIO_PRESET_STEREO = 0x0200,
	AMTVAUDIO_PRESET_LANG_A = 0x1000,
	AMTVAUDIO_PRESET_LANG_B = 0x2000,
	AMTVAUDIO_PRESET_LANG_C = 0x4000
} TVAudioMode;
typedef enum {
	UOP_FLAG_Play_Title_Or_AtTime = 0x00000001,
	UOP_FLAG_Play_Chapter = 0x00000002,
	UOP_FLAG_Play_Title = 0x00000004,
	UOP_FLAG_Stop = 0x00000008,
	UOP_FLAG_ReturnFromSubMenu = 0x00000010,
	UOP_FLAG_Play_Chapter_Or_AtTime = 0x00000020,
	UOP_FLAG_PlayPrev_Or_Replay_Chapter = 0x00000040,
	UOP_FLAG_PlayNext_Chapter = 0x00000080,
	UOP_FLAG_Play_Forwards = 0x00000100,
	UOP_FLAG_Play_Backwards = 0x00000200,
	UOP_FLAG_ShowMenu_Title = 0x00000400,
	UOP_FLAG_ShowMenu_Root = 0x00000800,
	UOP_FLAG_ShowMenu_SubPic = 0x00001000,
	UOP_FLAG_ShowMenu_Audio = 0x00002000,
	UOP_FLAG_ShowMenu_Angle = 0x00004000,
	UOP_FLAG_ShowMenu_Chapter = 0x00008000,
	UOP_FLAG_Resume = 0x00010000,
	UOP_FLAG_Select_Or_Activate_Button = 0x00020000,
	UOP_FLAG_Still_Off = 0x00040000,
	UOP_FLAG_Pause_On = 0x00080000,
	UOP_FLAG_Select_Audio_Stream = 0x00100000,
	UOP_FLAG_Select_SubPic_Stream = 0x00200000,
	UOP_FLAG_Select_Angle = 0x00400000,
	UOP_FLAG_Select_Karaoke_Audio_Presentation_Mode = 0x00800000,
	UOP_FLAG_Select_Video_Mode_Preference = 0x01000000
} VALID_UOP_FLAG;
typedef enum {
	VfwCaptureDialog_Source = 0x01,
	VfwCaptureDialog_Format = 0x02,
	VfwCaptureDialog_Display = 0x04
} VfwCaptureDialogs;
typedef enum {
	VfwCompressDialog_Config = 0x01,
	VfwCompressDialog_About = 0x02,
	VfwCompressDialog_QueryConfig = 0x04,
	VfwCompressDialog_QueryAbout = 0x08
} VfwCompressDialogs;
typedef enum tagVideoControlFlags {
	VideoControlFlag_FlipHorizontal = 0x0001,
	VideoControlFlag_FlipVertical = 0x0002,
	VideoControlFlag_ExternalTriggerEnable = 0x0004,
	VideoControlFlag_Trigger = 0x0008
} VideoControlFlags;
typedef enum {
	ConstantBitRate = 0,
	VariableBitRateAverage,
	VariableBitRatePeak
} VIDEOENCODER_BITRATE_MODE;
typedef enum tagVideoProcAmpFlags {
	VideoProcAmp_Flags_Auto = 0x0001,
	VideoProcAmp_Flags_Manual = 0x0002
} VideoProcAmpFlags;
typedef enum tagVideoProcAmpProperty {
	VideoProcAmp_Brightness,
	VideoProcAmp_Contrast,
	VideoProcAmp_Hue,
	VideoProcAmp_Saturation,
	VideoProcAmp_Sharpness,
	VideoProcAmp_Gamma,
	VideoProcAmp_ColorEnable,
	VideoProcAmp_WhiteBalance,
	VideoProcAmp_BacklightCompensation,
	VideoProcAmp_Gain
} VideoProcAmpProperty;
enum VMR_ASPECT_RATIO_MODE {
	VMR_ARMODE_NONE,
	VMR_ARMODE_LETTER_BOX
};
typedef enum {
	DeinterlacePref_NextBest = 0x01,
	DeinterlacePref_BOB = 0x02,
	DeinterlacePref_Weave = 0x04,
	DeinterlacePref_Mask = 0x07
} VMRDeinterlacePrefs;
typedef enum {
	DeinterlaceTech_Unknown = 0x0000,
	DeinterlaceTech_BOBLineReplicate = 0x0001,
	DeinterlaceTech_BOBVerticalStretch = 0x0002,
	DeinterlaceTech_MedianFiltering = 0x0004,
	DeinterlaceTech_EdgeFiltering = 0x0010,
	DeinterlaceTech_FieldAdaptive = 0x0020,
	DeinterlaceTech_PixelAdaptive = 0x0040,
	DeinterlaceTech_MotionVectorSteered = 0x0080
} VMRDeinterlaceTech;
typedef enum {
	MixerPref_NoDecimation = 0x00000001,
	MixerPref_DecimateOutput = 0x00000002,
	MixerPref_ARAdjustXorY = 0x00000004,
	MixerPref_DecimationReserved = 0x00000008,
	MixerPref_DecimateMask = 0x0000000F,
	MixerPref_BiLinearFiltering = 0x00000010,
	MixerPref_PointFiltering = 0x00000020,
	MixerPref_FilteringMask = 0x000000F0,
	MixerPref_RenderTargetRGB = 0x00000100,
	MixerPref_RenderTargetYUV = 0x00001000,
	MixerPref_RenderTargetYUV420 = 0x00000200,
	MixerPref_RenderTargetYUV422 = 0x00000400,
	MixerPref_RenderTargetYUV444 = 0x00000800,
	MixerPref_RenderTargetReserved = 0x0000E000,
	MixerPref_RenderTargetMask = 0x0000FF00,
	MixerPref_DynamicSwitchToBOB = 0x00010000,
	MixerPref_DynamicDecimateBy2 = 0x00020000,
	MixerPref_DynamicReserved = 0x000C0000,
	MixerPref_DynamicMask = 0x000F0000
} VMRMixerPrefs;
enum VMRMode {
	VMRMode_Windowed = 0x00000001,
	VMRMode_Windowless = 0x00000002,
	VMRMode_Renderless = 0x00000004,
	VMRMode_Mask = 0x00000007
};
typedef enum {
	VMRSample_SyncPoint = 0x00000001,
	VMRSample_Preroll = 0x00000002,
	VMRSample_Discontinuity = 0x00000004,
	VMRSample_TimeValid = 0x00000008
} VMRPresentationFlags;
typedef enum {
	RenderPrefs_ForceOffscreen = 0x00000001,
	RenderPrefs_ForceOverlays = 0x00000002,
	RenderPrefs_AllowOverlays = 0x00000000,
	RenderPrefs_AllowOffscreen = 0x00000000,
	RenderPrefs_DoNotRenderColorKeyAndBorder = 0x00000008,
	RenderPrefs_RestrictToInitialMonitor = 0x00000010,
	RenderPrefs_PreferAGPMemWhenMixing = 0x00000020,
	RenderPrefs_Mask = 0x0000003f
} VMRRenderPrefs;
typedef enum {
	AMAP_PIXELFORMAT_VALID = 0x01,
	AMAP_3D_TARGET = 0x02,
	AMAP_ALLOW_SYSMEM = 0x04,
	AMAP_FORCE_SYSMEM = 0x08,
	AMAP_DIRECTED_FLIP = 0x10,
	AMAP_DXVA_TARGET = 0x20
} VMRSurfaceAllocationFlags;
/*--- DirectShow Reference - DirectShow Structures */
typedef struct _AllocatorProperties {
	long cBuffers;
	long cbBuffer;
	long cbAlign;
	long cbPrefix;
} ALLOCATOR_PROPERTIES;
typedef struct {
	HRESULT hrVPEStatus;
	BOOL bDvdVolInvalid;
	BOOL bDvdVolUnknown;
	BOOL bNoLine21In;
	BOOL bNoLine21Out;
	int iNumStreams;
	int iNumStreamsFailed;
	DWORD dwFailedStreamsFlag;
} AM_DVD_RENDERSTATUS;
typedef struct _AMCOPPCommand {
	GUID macKDI;
	GUID guidCommandID;
	DWORD dwSequence;
	DWORD cbSizeData;
	BYTE CommandData[4056];
} AMCOPPCommand,*LPAMCOPPCommand;
typedef struct _AMCOPPSignature {
	BYTE Signature[256];
} AMCOPPSignature;
typedef struct _AMCOPPStatusInput {
	GUID rApp;
	GUID guidStatusRequestID;
	DWORD dwSequence;
	DWORD cbSizeData;
	BYTE StatusData[4056];
} AMCOPPStatusInput,*LPAMCOPPStatusInput;
typedef struct _AMCOPPStatusOutput {
	GUID macKDI;
	DWORD cbSizeData;
	BYTE COPPStatus[4076];
} AMCOPPStatusOutput,*LPAMCOPPStatusOutput;
typedef struct _AMMediaType {
	GUID majortype;
	GUID subtype;
	BOOL bFixedSizeSamples;
	BOOL bTemporalCompression;
	ULONG lSampleSize;
	GUID formattype;
	IUnknown *pUnk;
	ULONG cbFormat;
	BYTE *pbFormat;
} AM_MEDIA_TYPE;
typedef struct tagAM_SAMPLE2_PROPERTIES {
	DWORD cbData;
	DWORD dwTypeSpecificFlags;
	DWORD dwSampleFlags;
	LONG lActual;
	REFERENCE_TIME tStart;
	REFERENCE_TIME tStop;
	DWORD dwStreamId;
	AM_MEDIA_TYPE *pMediaType;
	BYTE *pbBuffer;
	LONG cbBuffer;
} AM_SAMPLE2_PROPERTIES;
typedef struct {
	REFERENCE_TIME tStart;
	REFERENCE_TIME tStop;
	DWORD dwStartCookie;
	DWORD dwStopCookie;
	DWORD dwFlags;
} AM_STREAM_INFO;
typedef struct {
	const CLSID *clsMajorType;
	const CLSID *clsMinorType;
} REGPINTYPES;
typedef REGPINTYPES AMOVIESETUP_MEDIATYPE,*PAMOVIESETUP_MEDIATYPE,*LPAMOVIESETUP_MEDIATYPE;
typedef struct {
	LPWSTR strName;
	BOOL bRendered;
	BOOL bOutput;
	BOOL bZero;
	BOOL bMany;
	const CLSID *clsConnectsToFilter;
	const WCHAR *strConnectsToPin;
	UINT nMediaTypes;
	const REGPINTYPES *lpMediaType;
} REGFILTERPINS;
typedef REGFILTERPINS AMOVIESETUP_PIN,*PAMOVIESETUP_PIN,*LPAMOVIESETUP_PIN;
typedef struct _AMOVIESETUP_FILTER {
	const CLSID *clsID;
	const WCHAR *strName;
	DWORD dwMerit;
	UINT nPins;
	const AMOVIESETUP_PIN *lpPin;
} AMOVIESETUP_FILTER,*PAMOVIESETUP_FILTER,*LPAMOVIESETUP_FILTER;
typedef struct _AUDIO_STREAM_CONFIG_CAPS {
	GUID guid;
	ULONG MinimumChannels;
	ULONG MaximumChannels;
	ULONG ChannelsGranularity;
	ULONG MinimumBitsPerSample;
	ULONG MaximumBitsPerSample;
	ULONG BitsPerSampleGranularity;
	ULONG MinimumSampleFrequency;
	ULONG MaximumSampleFrequency;
	ULONG SampleFrequencyGranularity;
} AUDIO_STREAM_CONFIG_CAPS;
struct CodecAPIEventData {
	GUID guid;
	DWORD dataLength;
	DWORD reserved[3];
};
typedef struct tagCOLORKEY {
	DWORD KeyType;
	DWORD PaletteIndex;
	COLORREF LowColorValue;
	COLORREF HighColorValue;
} COLORKEY;
#define CK_NOCOLORKEY 0x00000000
#define CK_INDEX 0x00000001
#define CK_RGB 0x00000002
typedef struct {
	DWORD dw1;
	DWORD dw2;
} DDCOLORKEY;
typedef struct tagDVD_AudioAttributes {
	DVD_AUDIO_APPMODE AppMode;
	DVD_AUDIO_FORMAT AudioFormat; 
	LCID Language;
	DVD_AUDIO_LANG_EXT LanguageExtension;
	BOOL fHasMultichannelInfo; 
	DWORD dwFrequency;
	BYTE bQuantization;
	BYTE bNumberOfChannels;
	DWORD dwReserved[2];
} DVD_AudioAttributes;
typedef struct tagDVD_DECODER_CAPS {
	DWORD dwSize;
	DWORD dwAudioCaps;
	double dFwdMaxRateVideo;
	double dFwdMaxRateAudio;
	double dFwdMaxRateSP;
	double dBwdMaxRateVideo; 
	double dBwdMaxRateAudio;
	double dBwdMaxRateSP;
	DWORD dwRes1;
	DWORD dwRes2;
	DWORD dwRes3;
	DWORD dwRes4;
} DVD_DECODER_CAPS;
#define DVD_AUDIO_CAPS_AC3 0x00000001
#define DVD_AUDIO_CAPS_MPEG2 0x00000002
#define DVD_AUDIO_CAPS_LPCM 0x00000004
#define DVD_AUDIO_CAPS_DTS 0x00000008
#define DVD_AUDIO_CAPS_SDDS 0x00000010
typedef struct tagDVD_HMSF_TIMECODE {
	BYTE bHours;
	BYTE bMinutes;
	BYTE bSeconds;
	BYTE bFrames;
} DVD_HMSF_TIMECODE;
typedef struct tagDVD_KaraokeAttributes {
	BYTE bVersion;
	BOOL fMasterOfCeremoniesInGuideVocal1;
	BOOL fDuet;
	DVD_KARAOKE_ASSIGNMENT ChannelAssignment;
	WORD wChannelContents[8];
} DVD_KaraokeAttributes;
typedef struct tagDVD_MUA_Coeff {
	double log2_alpha;
	double log2_beta;
} DVD_MUA_Coeff;
typedef struct tagDVD_MUA_MixingInfo {
	BOOL fMixTo0;
	BOOL fMixTo1;
	BOOL fMix0InPhase;
	BOOL fMix1InPhase;
	DWORD dwSpeakerPosition;
} DVD_MUA_MixingInfo;
#define KSAUDIO_SPEAKER_LEFT 0x00000001
#define KSAUDIO_SPEAKER_RIGHT 0x00000002
#define KSAUDIO_SPEAKER_CENTER 0x00000004
#define KSAUDIO_SPEAKER_SURROUND_LEFT 0x00000008
#define KSAUDIO_SPEAKER_SURROUND_RIGHT 0x00000010
#define KSAUDIO_SPEAKER_SUBWOOFER 0x00000020
#define KSAUDIO_SPEAKER_LEFT_OF_CENTER 0x00000040
#define KSAUDIO_SPEAKER_RIGHT_OF_CENTER 0x00000080
#define KSAUDIO_SPEAKER_SURROUND_MONO 0x00000100
#define KSAUDIO_SPEAKER_SIDE_LEFT 0x00000200
#define KSAUDIO_SPEAKER_SIDE_RIGHT 0x00000400
#define KSAUDIO_SPEAKER_TOP 0x00000800
typedef struct tagDVD_MultichannelAudioAttributes {
	DVD_MUA_MixingInfo Info[8];
	DVD_MUA_Coeff Coeff[8];
} DVD_MultichannelAudioAttributes;
typedef struct tagDVD_PLAYBACK_LOCATION {
	ULONG TitleNum;
	ULONG ChapterNum; 
	ULONG TimeCode;
} DVD_PLAYBACK_LOCATION;
typedef struct tagDVD_PLAYBACK_LOCATION2 {
	ULONG TitleNum;
	ULONG ChapterNum;
	DVD_HMSF_TIMECODE TimeCode;
	ULONG TimeCodeFlags;
} DVD_PLAYBACK_LOCATION2;
typedef struct tagDVD_SubpictureAttributes {
	DVD_SUBPICTURE_TYPE Type;
	DVD_SUBPICTURE_CODING CodingMode;
	LCID Language;
	DVD_SUBPICTURE_LANG_EXT LanguageExtension;
} DVD_SubpictureAttributes;
typedef struct tagDVD_TIMECODE {
	ULONG Hours1:4; 
	ULONG Hours10:4; 
	ULONG Minutes1:4; 
	ULONG Minutes10:4; 
	ULONG Seconds1:4; 
	ULONG Seconds10:4; 
	ULONG Frames1:4; 
	ULONG Frames10:2; 
	ULONG FrameRateCode:2; 
} DVD_TIMECODE;
typedef struct tagDVD_VideoAttributes {
	BOOL fPanscanPermitted;
	BOOL fLetterboxPermitted;
	ULONG ulAspectX;
	ULONG ulAspectY;
	ULONG ulFrameRate;
	ULONG ulFrameHeight;
	DVD_VIDEO_COMPRESSION Compression;
	BOOL fLine21Field1InGOP;
	BOOL fLine21Field2InGOP;
	ULONG ulSourceResolutionX;
	ULONG ulSourceResolutionY;
	BOOL fIsSourceLetterboxed;
	BOOL fIsFilmMode;
} DVD_VideoAttributes;
struct tagDVD_MenuAttributes {
	BOOL fCompatibleRegion[8];
	DVD_VideoAttributes VideoAttributes;
	BOOL fAudioPresent;
	DVD_AudioAttributes AudioAttributes;
	BOOL fSubpicturePresent;
	DVD_SubpictureAttributes SubpictureAttributes;
} DVD_MenuAttributes;
typedef struct tagDVD_TitleMainAttributes {
	DVD_TITLE_APPMODE AppMode;
	DVD_VideoAttributes VideoAttributes;
	ULONG ulNumberOfAudioStreams;
	DVD_AudioAttributes AudioAttributes[8];
	DVD_MultichannelAudioAttributes MultichannelAudioAttributes[8];
	ULONG ulNumberOfSubpictureStreams;
	DVD_SubpictureAttributes SubpictureAttributes[32];
} DVD_TitleAttributes;
typedef struct tag_DVINFO {
	DWORD dwDVAAuxSrc;
	DWORD dwDVAAuxCtl;
	DWORD dwDVAAuxSrc1;
	DWORD dwDVAAuxCtl1;
	DWORD dwDVVAuxSrc;
	DWORD dwDVVAuxCtl;
	DWORD dwDVReserved[2];
} DVINFO,*PDVINFO;
/***************
#define MAX_FILTER_NAME 128
typedef struct _FilterInfo {
	WCHAR achName[MAX_FILTER_NAME]; 
	IFilterGraph *pGraph;
} FILTER_INFO;
***************/
typedef struct _NORMALIZEDRECT {
	float left;
	float top;
	float right;
	float bottom;
} NORMALIZEDRECT,*PNORMALIZEDRECT;
#define MAX_PIN_NAME 128
typedef struct _PinInfo {
	IBaseFilter *pFilter;
	PIN_DIRECTION dir;
	WCHAR achName[MAX_PIN_NAME];
} PIN_INFO;
typedef struct{ 
	QualityMessageType Type;
	long Proportion;
	REFERENCE_TIME Late;
	REFERENCE_TIME TimeStamp;
} Quality;
typedef struct {
	CLSID clsMedium;
	DWORD dw1;
	DWORD dw2;
} REGPINMEDIUM;
typedef struct {
	DWORD dwFlags;
	UINT cInstances;
	UINT nMediaTypes; 
	const REGPINTYPES *lpMediaType;
	UINT nMediums;
	const REGPINMEDIUM *lpMedium;
	const CLSID *clsPinCategory;
} REGFILTERPINS2;
typedef struct {
	DWORD dwVersion;
	DWORD dwMerit;
	union {
		struct {
			ULONG cPins;
			const REGFILTERPINS *rgPins;
		};
		struct {
			ULONG cPins2;
			const REGFILTERPINS2 *rgPins2;
		};
	};
} REGFILTER2;
typedef struct {
	ULONG stream_id;
	DWORD dwMediaSampleContent;
	ULONG ulSubstreamFilterValue;
	int iDataOffset;
} STREAM_ID_MAP;
#define MPEG2_PROGRAM_STREAM_MAP 0x00000000
#define MPEG2_PROGRAM_ELEMENTARY_STREAM 0x00000001
#define MPEG2_PROGRAM_DIRECTORY_PES_PACKET 0x00000002
#define MPEG2_PROGRAM_PACK_HEADER 0x00000003
#define MPEG2_PROGRAM_PES_STREAM 0x00000004
#define MPEG2_PROGRAM_SYSTEM_HEADER 0x00000005
#define SUBSTREAM_FILTER_VAL_NONE 0x10000000
typedef struct tagTIMECODE {
	WORD wFrameRate;
	WORD wFrameFract;
	DWORD dwFrames;
} TIMECODE;
#define ED_FORMAT_SMPTE_30 0x00001196
#define ED_FORMAT_SMPTE_30DROP 0x00001197
#define ED_FORMAT_SMPTE_25 0x00001198
#define ED_FORMAT_SMPTE_24 0x00001199
typedef struct tagTIMECODE_SAMPLE {
	LONGLONG qwTick;
	TIMECODE timecode;
	DWORD dwUser;
	DWORD dwFlags;
} TIMECODE_SAMPLE;
/*#define AM_TIMECODE_FLAG_FCM */
/*#define AM_TIMECODE_FLAG_CF */
/*#define AM_TIMECODE_FLAG_FIELD */
/*#define AM_TIMECODE_FLAG_DF */
/*#define AM_TIMECODE_COLORFRAME */
/*#define AM_TIMECODE_COLORSEQUENCE */
/*#define AM_TIMECODE_FILMSEQUENCE_TYPE */
typedef struct _VIDEO_STREAM_CONFIG_CAPS {
	GUID guid;
	ULONG VideoStandard;
	SIZE InputSize;
	SIZE MinCroppingSize;
	SIZE MaxCroppingSize;
	int CropGranularityX;
	int CropGranularityY;
	int CropAlignX;
	int CropAlignY;
	SIZE MinOutputSize;
	SIZE MaxOutputSize;
	int OutputGranularityX;
	int OutputGranularityY;
	int StretchTapsX;
	int StretchTapsY;
	int ShrinkTapsX;
	int ShrinkTapsY;
	LONGLONG MinFrameInterval;
	LONGLONG MaxFrameInterval;
	LONG MinBitsPerSecond;
	LONG MaxBitsPerSecond;
} VIDEO_STREAM_CONFIG_CAPS;
typedef struct tagVMRALLOCATIONINFO {
	DWORD dwFlags;
	LPBITMAPINFOHEADER lpHdr;
	LPDDPIXELFORMAT lpPixFmt;
	SIZE szAspectRatio;
	DWORD dwMinBuffers;
	DWORD dwMaxBuffers;
	DWORD dwInterlaceFlags;
	SIZE szNativeSize;
} VMRALLOCATIONINFO;
/**********
typedef struct _VMRALPHABITMAP {
	DWORD dwFlags;
	HDC hdc;
	LPDIRECTDRAWSURFACE7 pDDS;
	RECT rSrc;
	NORMALIZEDRECT rDest;
	FLOAT fAlpha;
	COLORREF clrSrcKey;
} VMRALPHABITMAP,*PVMRALPHABITMAP;
**********/
#define VMRBITMAP_DISABLE 0x00000001
#define VMRBITMAP_HDC 0x00000002
#define VMRBITMAP_ENTIREDDS 0x00000004
#define VMRBITMAP_SRCCOLORKEY 0x00000008
#define VMRBITMAP_SRCRECT 0x00000010
typedef struct _VMRDeinterlaceCaps {
	DWORD dwSize;
	DWORD dwNumPreviousOutputFrames;
	DWORD dwNumForwardRefSamples;
	DWORD dwNumBackwardRefSamples;
	VMRDeinterlaceTech DeinterlaceTechnology;
} VMRDeinterlaceCaps;
typedef struct _VMRFrequency {
	DWORD dwNumerator;
	DWORD dwDenominator;
} VMRFrequency;
typedef struct tagVMRGUID {
	GUID *pGUID;
	GUID GUID;
} VMRGUID;
typedef struct tagVMRMONITORINFO {
	VMRGUID guid;
	RECT rcMonitor;
	HMONITOR hMon;
	DWORD dwFlags;
	wchar_t szDevice[32];
	wchar_t szDescription[256];
} VMRMONITORINFO;
/**********
typedef struct tagVMRPRESENTATIONINFO {
	DWORD dwFlags;
	LPDIRECTDRAWSURFACE7 lpSurf;
	REFERENCE_TIME rtStart;
	REFERENCE_TIME rtEnd;
	SIZE szAspectRatio;
	RECT rcSrc;
	RECT rcDst;
	DWORD dwTypeSpecificFlags;
	DWORD dwInterlaceFlags;
} VMRPRESENTATIONINFO;
**********/
typedef struct _VMRVideoDesc {
	DWORD dwSize;
	DWORD dwSampleWidth;
	DWORD dwSampleHeight;
	BOOL SingleFieldPerSample;
	DWORD dwFourCC;
	VMRFrequency InputSampleFreq;
	VMRFrequency OutputFrameFreq;
} VMRVideoDesc;
/**********
typedef struct _VMRVIDEOSTREAMINFO {
	LPDIRECTDRAWSURFACE7 pddsVideoSurface;
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwStrmID;
	FLOAT fAlpha;
	DDCOLORKEY ddClrKey;
	NORMALIZEDRECT rNormal;
} VMRVIDEOSTREAMINFO;
**********/
/*--- DirectShow Reference - Interfaces */
#define INTERFACE IAMAnalogVideoDecoder
DECLARE_INTERFACE_(IAMAnalogVideoDecoder, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD_(HRESULT,get_AvailableTVFormats)(THIS_ long*) PURE;
	STDMETHOD_(HRESULT,get_HorizontalLocked)(THIS_ long*) PURE;
	STDMETHOD_(HRESULT,get_NumberOfLines)(THIS_ long*) PURE;
	STDMETHOD_(HRESULT,get_OutputEnable)(THIS_ long*) PURE;
	STDMETHOD_(HRESULT,get_TVFormat)(THIS_ long*) PURE;
	STDMETHOD_(HRESULT,get_VCRHorizontalLocking)(THIS_ long*) PURE;
	STDMETHOD_(HRESULT,put_OutputEnable)(THIS_ long) PURE;
	STDMETHOD_(HRESULT,put_TVFormat)(THIS_ long) PURE;
	STDMETHOD_(HRESULT,put_VCRHorizontalLocking)(THIS_ long) PURE;
};
#undef INTERFACE
#define INTERFACE IAMAudioInputMixer
DECLARE_INTERFACE_(IAMAudioInputMixer, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD_(HRESULT,get_Bass)(THIS_ double*) PURE;
	STDMETHOD_(HRESULT,get_BassRange)(THIS_ double*) PURE;
	STDMETHOD_(HRESULT,get_Enable)(THIS_ BOOL*) PURE;
	STDMETHOD_(HRESULT,get_Loudness)(THIS_ BOOL*) PURE;
	STDMETHOD_(HRESULT,get_MixLevel)(THIS_ double*) PURE;
	STDMETHOD_(HRESULT,get_Mono)(THIS_ BOOL*) PURE;
	STDMETHOD_(HRESULT,get_Pan)(THIS_ double*) PURE;
	STDMETHOD_(HRESULT,get_Treble)(THIS_ double*) PURE;
	STDMETHOD_(HRESULT,get_TrebleRange)(THIS_ double*) PURE;
	STDMETHOD_(HRESULT,put_Bass)(THIS_ double) PURE;
	STDMETHOD_(HRESULT,put_Enable)(THIS_ BOOL) PURE;
	STDMETHOD_(HRESULT,put_Loudness)(THIS_ BOOL) PURE;
	STDMETHOD_(HRESULT,put_MixLevel)(THIS_ double) PURE;
	STDMETHOD_(HRESULT,put_Mono)(THIS_ BOOL) PURE;
	STDMETHOD_(HRESULT,put_Pan)(THIS_ double) PURE;
	STDMETHOD_(HRESULT,put_Treble)(THIS_ double) PURE;
};
#undef INTERFACE
#define INTERFACE IAMAudioRendererStats
DECLARE_INTERFACE_(IAMAudioRendererStats, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD_(HRESULT,GetStatParam)(THIS_ DWORD,DWORD*,DWORD*) PURE;
};
#undef INTERFACE
#define INTERFACE IAMBufferNegotiation
DECLARE_INTERFACE_(IAMBufferNegotiation, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD_(HRESULT,GetAllocatorProperties)(THIS_ ALLOCATOR_PROPERTIES*) PURE;
	STDMETHOD_(HRESULT,SuggestAllocatorProperties)(THIS_ const ALLOCATOR_PROPERTIES*) PURE;
};
#undef INTERFACE
#define INTERFACE IAMCameraControl
DECLARE_INTERFACE_(IAMCameraControl, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD_(HRESULT,Get)(THIS_ long,long*,long*) PURE;
	STDMETHOD_(HRESULT,GetRange)(THIS_ long,long*,long*,long*,long*,long*) PURE;
	STDMETHOD_(HRESULT,Set)(THIS_ long,long,long) PURE;
};
#undef INTERFACE

#define INTERFACE IAMCertifiedOutputProtection
DECLARE_INTERFACE_(IAMCertifiedOutputProtection, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD_(HRESULT,KeyExchange)(THIS_ GUID*,BYTE**,DWORD*) PURE;
	STDMETHOD_(HRESULT,ProtectionCommand)(THIS_ const AMCOPPCommand*) PURE;
	STDMETHOD_(HRESULT,ProtectionStatus)(THIS_ const AMCOPPStatusInput*,AMCOPPStatusOutput*) PURE;
	STDMETHOD_(HRESULT,SessionSequenceStart)(THIS_ const AMCOPPSignature*) PURE;
};
#undef INTERFACE

#ifdef __cplusplus
}
#endif
#endif
