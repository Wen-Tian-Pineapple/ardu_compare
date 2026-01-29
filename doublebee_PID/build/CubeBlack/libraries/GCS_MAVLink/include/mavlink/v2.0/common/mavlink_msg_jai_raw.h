#pragma once
// MESSAGE JAI_RAW PACKING

#define MAVLINK_MSG_ID_JAI_RAW 13500


typedef struct __mavlink_jai_raw_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.*/
 float rol; /*< [rad] Roll*/
 float pit; /*< [rad] Pitch*/
 float yaw; /*< [rad] Yaw*/
 float drol; /*< [rad/s] Dot Roll*/
 float dpit; /*< [rad/s] Dot Pitch*/
 float dyaw; /*< [rad/s] Dot Yaw*/
 float xa; /*< [m/s/s] xacceleration*/
 float ya; /*< [m/s/s] yacceleration*/
 float za; /*< [m/s/s] zacceleration*/
 float ur; /*< [unit] wheel output right*/
 float ul; /*< [unit] wheel output left*/
 float disired_pit; /*< [rad] desired_dot_dot_pitch*/
 float desired_dpit; /*< [rad/s] PWM1*/
 float beta; /*<  beta*/
 float Thr_out; /*<  Thr_out*/
} mavlink_jai_raw_t;

#define MAVLINK_MSG_ID_JAI_RAW_LEN 68
#define MAVLINK_MSG_ID_JAI_RAW_MIN_LEN 40
#define MAVLINK_MSG_ID_13500_LEN 68
#define MAVLINK_MSG_ID_13500_MIN_LEN 40

#define MAVLINK_MSG_ID_JAI_RAW_CRC 93
#define MAVLINK_MSG_ID_13500_CRC 93



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_JAI_RAW { \
    13500, \
    "JAI_RAW", \
    16, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_jai_raw_t, time_usec) }, \
         { "rol", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_jai_raw_t, rol) }, \
         { "pit", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_jai_raw_t, pit) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_jai_raw_t, yaw) }, \
         { "drol", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_jai_raw_t, drol) }, \
         { "dpit", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_jai_raw_t, dpit) }, \
         { "dyaw", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_jai_raw_t, dyaw) }, \
         { "xa", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_jai_raw_t, xa) }, \
         { "ya", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_jai_raw_t, ya) }, \
         { "za", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_jai_raw_t, za) }, \
         { "ur", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_jai_raw_t, ur) }, \
         { "ul", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_jai_raw_t, ul) }, \
         { "disired_pit", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_jai_raw_t, disired_pit) }, \
         { "desired_dpit", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_jai_raw_t, desired_dpit) }, \
         { "beta", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_jai_raw_t, beta) }, \
         { "Thr_out", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_jai_raw_t, Thr_out) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_JAI_RAW { \
    "JAI_RAW", \
    16, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_jai_raw_t, time_usec) }, \
         { "rol", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_jai_raw_t, rol) }, \
         { "pit", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_jai_raw_t, pit) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_jai_raw_t, yaw) }, \
         { "drol", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_jai_raw_t, drol) }, \
         { "dpit", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_jai_raw_t, dpit) }, \
         { "dyaw", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_jai_raw_t, dyaw) }, \
         { "xa", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_jai_raw_t, xa) }, \
         { "ya", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_jai_raw_t, ya) }, \
         { "za", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_jai_raw_t, za) }, \
         { "ur", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_jai_raw_t, ur) }, \
         { "ul", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_jai_raw_t, ul) }, \
         { "disired_pit", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_jai_raw_t, disired_pit) }, \
         { "desired_dpit", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_jai_raw_t, desired_dpit) }, \
         { "beta", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_jai_raw_t, beta) }, \
         { "Thr_out", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_jai_raw_t, Thr_out) }, \
         } \
}
#endif

/**
 * @brief Pack a jai_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 * @param rol [rad] Roll
 * @param pit [rad] Pitch
 * @param yaw [rad] Yaw
 * @param drol [rad/s] Dot Roll
 * @param dpit [rad/s] Dot Pitch
 * @param dyaw [rad/s] Dot Yaw
 * @param xa [m/s/s] xacceleration
 * @param ya [m/s/s] yacceleration
 * @param za [m/s/s] zacceleration
 * @param ur [unit] wheel output right
 * @param ul [unit] wheel output left
 * @param disired_pit [rad] desired_dot_dot_pitch
 * @param desired_dpit [rad/s] PWM1
 * @param beta  beta
 * @param Thr_out  Thr_out
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_jai_raw_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, float rol, float pit, float yaw, float drol, float dpit, float dyaw, float xa, float ya, float za, float ur, float ul, float disired_pit, float desired_dpit, float beta, float Thr_out)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_JAI_RAW_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, rol);
    _mav_put_float(buf, 12, pit);
    _mav_put_float(buf, 16, yaw);
    _mav_put_float(buf, 20, drol);
    _mav_put_float(buf, 24, dpit);
    _mav_put_float(buf, 28, dyaw);
    _mav_put_float(buf, 32, xa);
    _mav_put_float(buf, 36, ya);
    _mav_put_float(buf, 40, za);
    _mav_put_float(buf, 44, ur);
    _mav_put_float(buf, 48, ul);
    _mav_put_float(buf, 52, disired_pit);
    _mav_put_float(buf, 56, desired_dpit);
    _mav_put_float(buf, 60, beta);
    _mav_put_float(buf, 64, Thr_out);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_JAI_RAW_LEN);
#else
    mavlink_jai_raw_t packet;
    packet.time_usec = time_usec;
    packet.rol = rol;
    packet.pit = pit;
    packet.yaw = yaw;
    packet.drol = drol;
    packet.dpit = dpit;
    packet.dyaw = dyaw;
    packet.xa = xa;
    packet.ya = ya;
    packet.za = za;
    packet.ur = ur;
    packet.ul = ul;
    packet.disired_pit = disired_pit;
    packet.desired_dpit = desired_dpit;
    packet.beta = beta;
    packet.Thr_out = Thr_out;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_JAI_RAW_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_JAI_RAW;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_JAI_RAW_MIN_LEN, MAVLINK_MSG_ID_JAI_RAW_LEN, MAVLINK_MSG_ID_JAI_RAW_CRC);
}

/**
 * @brief Pack a jai_raw message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 * @param rol [rad] Roll
 * @param pit [rad] Pitch
 * @param yaw [rad] Yaw
 * @param drol [rad/s] Dot Roll
 * @param dpit [rad/s] Dot Pitch
 * @param dyaw [rad/s] Dot Yaw
 * @param xa [m/s/s] xacceleration
 * @param ya [m/s/s] yacceleration
 * @param za [m/s/s] zacceleration
 * @param ur [unit] wheel output right
 * @param ul [unit] wheel output left
 * @param disired_pit [rad] desired_dot_dot_pitch
 * @param desired_dpit [rad/s] PWM1
 * @param beta  beta
 * @param Thr_out  Thr_out
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_jai_raw_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,float rol,float pit,float yaw,float drol,float dpit,float dyaw,float xa,float ya,float za,float ur,float ul,float disired_pit,float desired_dpit,float beta,float Thr_out)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_JAI_RAW_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, rol);
    _mav_put_float(buf, 12, pit);
    _mav_put_float(buf, 16, yaw);
    _mav_put_float(buf, 20, drol);
    _mav_put_float(buf, 24, dpit);
    _mav_put_float(buf, 28, dyaw);
    _mav_put_float(buf, 32, xa);
    _mav_put_float(buf, 36, ya);
    _mav_put_float(buf, 40, za);
    _mav_put_float(buf, 44, ur);
    _mav_put_float(buf, 48, ul);
    _mav_put_float(buf, 52, disired_pit);
    _mav_put_float(buf, 56, desired_dpit);
    _mav_put_float(buf, 60, beta);
    _mav_put_float(buf, 64, Thr_out);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_JAI_RAW_LEN);
#else
    mavlink_jai_raw_t packet;
    packet.time_usec = time_usec;
    packet.rol = rol;
    packet.pit = pit;
    packet.yaw = yaw;
    packet.drol = drol;
    packet.dpit = dpit;
    packet.dyaw = dyaw;
    packet.xa = xa;
    packet.ya = ya;
    packet.za = za;
    packet.ur = ur;
    packet.ul = ul;
    packet.disired_pit = disired_pit;
    packet.desired_dpit = desired_dpit;
    packet.beta = beta;
    packet.Thr_out = Thr_out;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_JAI_RAW_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_JAI_RAW;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_JAI_RAW_MIN_LEN, MAVLINK_MSG_ID_JAI_RAW_LEN, MAVLINK_MSG_ID_JAI_RAW_CRC);
}

/**
 * @brief Encode a jai_raw struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param jai_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_jai_raw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_jai_raw_t* jai_raw)
{
    return mavlink_msg_jai_raw_pack(system_id, component_id, msg, jai_raw->time_usec, jai_raw->rol, jai_raw->pit, jai_raw->yaw, jai_raw->drol, jai_raw->dpit, jai_raw->dyaw, jai_raw->xa, jai_raw->ya, jai_raw->za, jai_raw->ur, jai_raw->ul, jai_raw->disired_pit, jai_raw->desired_dpit, jai_raw->beta, jai_raw->Thr_out);
}

/**
 * @brief Encode a jai_raw struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param jai_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_jai_raw_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_jai_raw_t* jai_raw)
{
    return mavlink_msg_jai_raw_pack_chan(system_id, component_id, chan, msg, jai_raw->time_usec, jai_raw->rol, jai_raw->pit, jai_raw->yaw, jai_raw->drol, jai_raw->dpit, jai_raw->dyaw, jai_raw->xa, jai_raw->ya, jai_raw->za, jai_raw->ur, jai_raw->ul, jai_raw->disired_pit, jai_raw->desired_dpit, jai_raw->beta, jai_raw->Thr_out);
}

/**
 * @brief Send a jai_raw message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 * @param rol [rad] Roll
 * @param pit [rad] Pitch
 * @param yaw [rad] Yaw
 * @param drol [rad/s] Dot Roll
 * @param dpit [rad/s] Dot Pitch
 * @param dyaw [rad/s] Dot Yaw
 * @param xa [m/s/s] xacceleration
 * @param ya [m/s/s] yacceleration
 * @param za [m/s/s] zacceleration
 * @param ur [unit] wheel output right
 * @param ul [unit] wheel output left
 * @param disired_pit [rad] desired_dot_dot_pitch
 * @param desired_dpit [rad/s] PWM1
 * @param beta  beta
 * @param Thr_out  Thr_out
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_jai_raw_send(mavlink_channel_t chan, uint64_t time_usec, float rol, float pit, float yaw, float drol, float dpit, float dyaw, float xa, float ya, float za, float ur, float ul, float disired_pit, float desired_dpit, float beta, float Thr_out)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_JAI_RAW_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, rol);
    _mav_put_float(buf, 12, pit);
    _mav_put_float(buf, 16, yaw);
    _mav_put_float(buf, 20, drol);
    _mav_put_float(buf, 24, dpit);
    _mav_put_float(buf, 28, dyaw);
    _mav_put_float(buf, 32, xa);
    _mav_put_float(buf, 36, ya);
    _mav_put_float(buf, 40, za);
    _mav_put_float(buf, 44, ur);
    _mav_put_float(buf, 48, ul);
    _mav_put_float(buf, 52, disired_pit);
    _mav_put_float(buf, 56, desired_dpit);
    _mav_put_float(buf, 60, beta);
    _mav_put_float(buf, 64, Thr_out);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_JAI_RAW, buf, MAVLINK_MSG_ID_JAI_RAW_MIN_LEN, MAVLINK_MSG_ID_JAI_RAW_LEN, MAVLINK_MSG_ID_JAI_RAW_CRC);
#else
    mavlink_jai_raw_t packet;
    packet.time_usec = time_usec;
    packet.rol = rol;
    packet.pit = pit;
    packet.yaw = yaw;
    packet.drol = drol;
    packet.dpit = dpit;
    packet.dyaw = dyaw;
    packet.xa = xa;
    packet.ya = ya;
    packet.za = za;
    packet.ur = ur;
    packet.ul = ul;
    packet.disired_pit = disired_pit;
    packet.desired_dpit = desired_dpit;
    packet.beta = beta;
    packet.Thr_out = Thr_out;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_JAI_RAW, (const char *)&packet, MAVLINK_MSG_ID_JAI_RAW_MIN_LEN, MAVLINK_MSG_ID_JAI_RAW_LEN, MAVLINK_MSG_ID_JAI_RAW_CRC);
#endif
}

/**
 * @brief Send a jai_raw message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_jai_raw_send_struct(mavlink_channel_t chan, const mavlink_jai_raw_t* jai_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_jai_raw_send(chan, jai_raw->time_usec, jai_raw->rol, jai_raw->pit, jai_raw->yaw, jai_raw->drol, jai_raw->dpit, jai_raw->dyaw, jai_raw->xa, jai_raw->ya, jai_raw->za, jai_raw->ur, jai_raw->ul, jai_raw->disired_pit, jai_raw->desired_dpit, jai_raw->beta, jai_raw->Thr_out);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_JAI_RAW, (const char *)jai_raw, MAVLINK_MSG_ID_JAI_RAW_MIN_LEN, MAVLINK_MSG_ID_JAI_RAW_LEN, MAVLINK_MSG_ID_JAI_RAW_CRC);
#endif
}

#if MAVLINK_MSG_ID_JAI_RAW_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_jai_raw_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, float rol, float pit, float yaw, float drol, float dpit, float dyaw, float xa, float ya, float za, float ur, float ul, float disired_pit, float desired_dpit, float beta, float Thr_out)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, rol);
    _mav_put_float(buf, 12, pit);
    _mav_put_float(buf, 16, yaw);
    _mav_put_float(buf, 20, drol);
    _mav_put_float(buf, 24, dpit);
    _mav_put_float(buf, 28, dyaw);
    _mav_put_float(buf, 32, xa);
    _mav_put_float(buf, 36, ya);
    _mav_put_float(buf, 40, za);
    _mav_put_float(buf, 44, ur);
    _mav_put_float(buf, 48, ul);
    _mav_put_float(buf, 52, disired_pit);
    _mav_put_float(buf, 56, desired_dpit);
    _mav_put_float(buf, 60, beta);
    _mav_put_float(buf, 64, Thr_out);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_JAI_RAW, buf, MAVLINK_MSG_ID_JAI_RAW_MIN_LEN, MAVLINK_MSG_ID_JAI_RAW_LEN, MAVLINK_MSG_ID_JAI_RAW_CRC);
#else
    mavlink_jai_raw_t *packet = (mavlink_jai_raw_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->rol = rol;
    packet->pit = pit;
    packet->yaw = yaw;
    packet->drol = drol;
    packet->dpit = dpit;
    packet->dyaw = dyaw;
    packet->xa = xa;
    packet->ya = ya;
    packet->za = za;
    packet->ur = ur;
    packet->ul = ul;
    packet->disired_pit = disired_pit;
    packet->desired_dpit = desired_dpit;
    packet->beta = beta;
    packet->Thr_out = Thr_out;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_JAI_RAW, (const char *)packet, MAVLINK_MSG_ID_JAI_RAW_MIN_LEN, MAVLINK_MSG_ID_JAI_RAW_LEN, MAVLINK_MSG_ID_JAI_RAW_CRC);
#endif
}
#endif

#endif

// MESSAGE JAI_RAW UNPACKING


/**
 * @brief Get field time_usec from jai_raw message
 *
 * @return [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 */
static inline uint64_t mavlink_msg_jai_raw_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field rol from jai_raw message
 *
 * @return [rad] Roll
 */
static inline float mavlink_msg_jai_raw_get_rol(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field pit from jai_raw message
 *
 * @return [rad] Pitch
 */
static inline float mavlink_msg_jai_raw_get_pit(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field yaw from jai_raw message
 *
 * @return [rad] Yaw
 */
static inline float mavlink_msg_jai_raw_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field drol from jai_raw message
 *
 * @return [rad/s] Dot Roll
 */
static inline float mavlink_msg_jai_raw_get_drol(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field dpit from jai_raw message
 *
 * @return [rad/s] Dot Pitch
 */
static inline float mavlink_msg_jai_raw_get_dpit(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field dyaw from jai_raw message
 *
 * @return [rad/s] Dot Yaw
 */
static inline float mavlink_msg_jai_raw_get_dyaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field xa from jai_raw message
 *
 * @return [m/s/s] xacceleration
 */
static inline float mavlink_msg_jai_raw_get_xa(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field ya from jai_raw message
 *
 * @return [m/s/s] yacceleration
 */
static inline float mavlink_msg_jai_raw_get_ya(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field za from jai_raw message
 *
 * @return [m/s/s] zacceleration
 */
static inline float mavlink_msg_jai_raw_get_za(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field ur from jai_raw message
 *
 * @return [unit] wheel output right
 */
static inline float mavlink_msg_jai_raw_get_ur(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field ul from jai_raw message
 *
 * @return [unit] wheel output left
 */
static inline float mavlink_msg_jai_raw_get_ul(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field disired_pit from jai_raw message
 *
 * @return [rad] desired_dot_dot_pitch
 */
static inline float mavlink_msg_jai_raw_get_disired_pit(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field desired_dpit from jai_raw message
 *
 * @return [rad/s] PWM1
 */
static inline float mavlink_msg_jai_raw_get_desired_dpit(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field beta from jai_raw message
 *
 * @return  beta
 */
static inline float mavlink_msg_jai_raw_get_beta(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field Thr_out from jai_raw message
 *
 * @return  Thr_out
 */
static inline float mavlink_msg_jai_raw_get_Thr_out(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Decode a jai_raw message into a struct
 *
 * @param msg The message to decode
 * @param jai_raw C-struct to decode the message contents into
 */
static inline void mavlink_msg_jai_raw_decode(const mavlink_message_t* msg, mavlink_jai_raw_t* jai_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    jai_raw->time_usec = mavlink_msg_jai_raw_get_time_usec(msg);
    jai_raw->rol = mavlink_msg_jai_raw_get_rol(msg);
    jai_raw->pit = mavlink_msg_jai_raw_get_pit(msg);
    jai_raw->yaw = mavlink_msg_jai_raw_get_yaw(msg);
    jai_raw->drol = mavlink_msg_jai_raw_get_drol(msg);
    jai_raw->dpit = mavlink_msg_jai_raw_get_dpit(msg);
    jai_raw->dyaw = mavlink_msg_jai_raw_get_dyaw(msg);
    jai_raw->xa = mavlink_msg_jai_raw_get_xa(msg);
    jai_raw->ya = mavlink_msg_jai_raw_get_ya(msg);
    jai_raw->za = mavlink_msg_jai_raw_get_za(msg);
    jai_raw->ur = mavlink_msg_jai_raw_get_ur(msg);
    jai_raw->ul = mavlink_msg_jai_raw_get_ul(msg);
    jai_raw->disired_pit = mavlink_msg_jai_raw_get_disired_pit(msg);
    jai_raw->desired_dpit = mavlink_msg_jai_raw_get_desired_dpit(msg);
    jai_raw->beta = mavlink_msg_jai_raw_get_beta(msg);
    jai_raw->Thr_out = mavlink_msg_jai_raw_get_Thr_out(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_JAI_RAW_LEN? msg->len : MAVLINK_MSG_ID_JAI_RAW_LEN;
        memset(jai_raw, 0, MAVLINK_MSG_ID_JAI_RAW_LEN);
    memcpy(jai_raw, _MAV_PAYLOAD(msg), len);
#endif
}
