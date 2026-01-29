#pragma once
// MESSAGE JAI_OUT PACKING

#define MAVLINK_MSG_ID_JAI_OUT 13600


typedef struct __mavlink_jai_out_t {
 float wh_r; /*< [rad] whe_right*/
 float wh_l; /*< [rad/s] whe_left*/
 float u_thr; /*< [unit] u_thr*/
 uint16_t pit_pwm; /*< [rad] pit_pwm*/
 uint8_t rc_state; /*< [rad] use_rc*/
} mavlink_jai_out_t;

#define MAVLINK_MSG_ID_JAI_OUT_LEN 15
#define MAVLINK_MSG_ID_JAI_OUT_MIN_LEN 15
#define MAVLINK_MSG_ID_13600_LEN 15
#define MAVLINK_MSG_ID_13600_MIN_LEN 15

#define MAVLINK_MSG_ID_JAI_OUT_CRC 193
#define MAVLINK_MSG_ID_13600_CRC 193



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_JAI_OUT { \
    13600, \
    "JAI_OUT", \
    5, \
    {  { "rc_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_jai_out_t, rc_state) }, \
         { "pit_pwm", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_jai_out_t, pit_pwm) }, \
         { "wh_r", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_jai_out_t, wh_r) }, \
         { "wh_l", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_jai_out_t, wh_l) }, \
         { "u_thr", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_jai_out_t, u_thr) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_JAI_OUT { \
    "JAI_OUT", \
    5, \
    {  { "rc_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_jai_out_t, rc_state) }, \
         { "pit_pwm", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_jai_out_t, pit_pwm) }, \
         { "wh_r", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_jai_out_t, wh_r) }, \
         { "wh_l", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_jai_out_t, wh_l) }, \
         { "u_thr", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_jai_out_t, u_thr) }, \
         } \
}
#endif

/**
 * @brief Pack a jai_out message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param rc_state [rad] use_rc
 * @param pit_pwm [rad] pit_pwm
 * @param wh_r [rad] whe_right
 * @param wh_l [rad/s] whe_left
 * @param u_thr [unit] u_thr
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_jai_out_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t rc_state, uint16_t pit_pwm, float wh_r, float wh_l, float u_thr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_JAI_OUT_LEN];
    _mav_put_float(buf, 0, wh_r);
    _mav_put_float(buf, 4, wh_l);
    _mav_put_float(buf, 8, u_thr);
    _mav_put_uint16_t(buf, 12, pit_pwm);
    _mav_put_uint8_t(buf, 14, rc_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_JAI_OUT_LEN);
#else
    mavlink_jai_out_t packet;
    packet.wh_r = wh_r;
    packet.wh_l = wh_l;
    packet.u_thr = u_thr;
    packet.pit_pwm = pit_pwm;
    packet.rc_state = rc_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_JAI_OUT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_JAI_OUT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_JAI_OUT_MIN_LEN, MAVLINK_MSG_ID_JAI_OUT_LEN, MAVLINK_MSG_ID_JAI_OUT_CRC);
}

/**
 * @brief Pack a jai_out message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rc_state [rad] use_rc
 * @param pit_pwm [rad] pit_pwm
 * @param wh_r [rad] whe_right
 * @param wh_l [rad/s] whe_left
 * @param u_thr [unit] u_thr
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_jai_out_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t rc_state,uint16_t pit_pwm,float wh_r,float wh_l,float u_thr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_JAI_OUT_LEN];
    _mav_put_float(buf, 0, wh_r);
    _mav_put_float(buf, 4, wh_l);
    _mav_put_float(buf, 8, u_thr);
    _mav_put_uint16_t(buf, 12, pit_pwm);
    _mav_put_uint8_t(buf, 14, rc_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_JAI_OUT_LEN);
#else
    mavlink_jai_out_t packet;
    packet.wh_r = wh_r;
    packet.wh_l = wh_l;
    packet.u_thr = u_thr;
    packet.pit_pwm = pit_pwm;
    packet.rc_state = rc_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_JAI_OUT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_JAI_OUT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_JAI_OUT_MIN_LEN, MAVLINK_MSG_ID_JAI_OUT_LEN, MAVLINK_MSG_ID_JAI_OUT_CRC);
}

/**
 * @brief Encode a jai_out struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param jai_out C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_jai_out_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_jai_out_t* jai_out)
{
    return mavlink_msg_jai_out_pack(system_id, component_id, msg, jai_out->rc_state, jai_out->pit_pwm, jai_out->wh_r, jai_out->wh_l, jai_out->u_thr);
}

/**
 * @brief Encode a jai_out struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param jai_out C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_jai_out_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_jai_out_t* jai_out)
{
    return mavlink_msg_jai_out_pack_chan(system_id, component_id, chan, msg, jai_out->rc_state, jai_out->pit_pwm, jai_out->wh_r, jai_out->wh_l, jai_out->u_thr);
}

/**
 * @brief Send a jai_out message
 * @param chan MAVLink channel to send the message
 *
 * @param rc_state [rad] use_rc
 * @param pit_pwm [rad] pit_pwm
 * @param wh_r [rad] whe_right
 * @param wh_l [rad/s] whe_left
 * @param u_thr [unit] u_thr
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_jai_out_send(mavlink_channel_t chan, uint8_t rc_state, uint16_t pit_pwm, float wh_r, float wh_l, float u_thr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_JAI_OUT_LEN];
    _mav_put_float(buf, 0, wh_r);
    _mav_put_float(buf, 4, wh_l);
    _mav_put_float(buf, 8, u_thr);
    _mav_put_uint16_t(buf, 12, pit_pwm);
    _mav_put_uint8_t(buf, 14, rc_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_JAI_OUT, buf, MAVLINK_MSG_ID_JAI_OUT_MIN_LEN, MAVLINK_MSG_ID_JAI_OUT_LEN, MAVLINK_MSG_ID_JAI_OUT_CRC);
#else
    mavlink_jai_out_t packet;
    packet.wh_r = wh_r;
    packet.wh_l = wh_l;
    packet.u_thr = u_thr;
    packet.pit_pwm = pit_pwm;
    packet.rc_state = rc_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_JAI_OUT, (const char *)&packet, MAVLINK_MSG_ID_JAI_OUT_MIN_LEN, MAVLINK_MSG_ID_JAI_OUT_LEN, MAVLINK_MSG_ID_JAI_OUT_CRC);
#endif
}

/**
 * @brief Send a jai_out message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_jai_out_send_struct(mavlink_channel_t chan, const mavlink_jai_out_t* jai_out)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_jai_out_send(chan, jai_out->rc_state, jai_out->pit_pwm, jai_out->wh_r, jai_out->wh_l, jai_out->u_thr);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_JAI_OUT, (const char *)jai_out, MAVLINK_MSG_ID_JAI_OUT_MIN_LEN, MAVLINK_MSG_ID_JAI_OUT_LEN, MAVLINK_MSG_ID_JAI_OUT_CRC);
#endif
}

#if MAVLINK_MSG_ID_JAI_OUT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_jai_out_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t rc_state, uint16_t pit_pwm, float wh_r, float wh_l, float u_thr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, wh_r);
    _mav_put_float(buf, 4, wh_l);
    _mav_put_float(buf, 8, u_thr);
    _mav_put_uint16_t(buf, 12, pit_pwm);
    _mav_put_uint8_t(buf, 14, rc_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_JAI_OUT, buf, MAVLINK_MSG_ID_JAI_OUT_MIN_LEN, MAVLINK_MSG_ID_JAI_OUT_LEN, MAVLINK_MSG_ID_JAI_OUT_CRC);
#else
    mavlink_jai_out_t *packet = (mavlink_jai_out_t *)msgbuf;
    packet->wh_r = wh_r;
    packet->wh_l = wh_l;
    packet->u_thr = u_thr;
    packet->pit_pwm = pit_pwm;
    packet->rc_state = rc_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_JAI_OUT, (const char *)packet, MAVLINK_MSG_ID_JAI_OUT_MIN_LEN, MAVLINK_MSG_ID_JAI_OUT_LEN, MAVLINK_MSG_ID_JAI_OUT_CRC);
#endif
}
#endif

#endif

// MESSAGE JAI_OUT UNPACKING


/**
 * @brief Get field rc_state from jai_out message
 *
 * @return [rad] use_rc
 */
static inline uint8_t mavlink_msg_jai_out_get_rc_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Get field pit_pwm from jai_out message
 *
 * @return [rad] pit_pwm
 */
static inline uint16_t mavlink_msg_jai_out_get_pit_pwm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field wh_r from jai_out message
 *
 * @return [rad] whe_right
 */
static inline float mavlink_msg_jai_out_get_wh_r(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field wh_l from jai_out message
 *
 * @return [rad/s] whe_left
 */
static inline float mavlink_msg_jai_out_get_wh_l(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field u_thr from jai_out message
 *
 * @return [unit] u_thr
 */
static inline float mavlink_msg_jai_out_get_u_thr(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a jai_out message into a struct
 *
 * @param msg The message to decode
 * @param jai_out C-struct to decode the message contents into
 */
static inline void mavlink_msg_jai_out_decode(const mavlink_message_t* msg, mavlink_jai_out_t* jai_out)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    jai_out->wh_r = mavlink_msg_jai_out_get_wh_r(msg);
    jai_out->wh_l = mavlink_msg_jai_out_get_wh_l(msg);
    jai_out->u_thr = mavlink_msg_jai_out_get_u_thr(msg);
    jai_out->pit_pwm = mavlink_msg_jai_out_get_pit_pwm(msg);
    jai_out->rc_state = mavlink_msg_jai_out_get_rc_state(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_JAI_OUT_LEN? msg->len : MAVLINK_MSG_ID_JAI_OUT_LEN;
        memset(jai_out, 0, MAVLINK_MSG_ID_JAI_OUT_LEN);
    memcpy(jai_out, _MAV_PAYLOAD(msg), len);
#endif
}
