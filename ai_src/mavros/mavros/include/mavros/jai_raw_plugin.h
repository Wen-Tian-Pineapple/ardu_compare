#ifndef MAVROS_JAI_RAW_PLUGIN_H
#define MAVROS_JAI_RAW_PLUGIN_H

#include <mavros/mavros_plugin.h>
#include <mavros_msgs/JaiRaw.h>
#include <pluginlib/class_list_macros.h>


namespace mavros {
namespace std_plugins {

class JaiRawPlugin : public plugin::PluginBase {
public:
    JaiRawPlugin() : PluginBase(), nh("~") { }

    void initialize(UAS &uas_) override {
        PluginBase::initialize(uas_);
        raw_pub = nh.advertise<mavros_msgs::JaiRaw>("jai_raw", 10);
        // enable_connection_cb();
    }

    Subscriptions get_subscriptions() override {
        return {
            make_handler(&JaiRawPlugin::handle_jai_raw)
        };
    }

private:
    ros::NodeHandle nh;
    ros::Publisher raw_pub;

    void handle_jai_raw(const mavlink::mavlink_message_t *msg, mavlink::common::msg::JAI_RAW &jai_raw) {
        auto jai_raw_msg = boost::make_shared<mavros_msgs::JaiRaw>();

        jai_raw_msg->header.stamp = ros::Time::now();
        jai_raw_msg->time_usec = jai_raw.time_usec;
        jai_raw_msg->rol = jai_raw.rol;
        jai_raw_msg->pit = jai_raw.pit;
        jai_raw_msg->yaw = jai_raw.yaw;
        jai_raw_msg->drol = jai_raw.drol;
        jai_raw_msg->dpit = jai_raw.dpit;
        jai_raw_msg->dyaw = jai_raw.dyaw;
        jai_raw_msg->xa = jai_raw.xa;
        jai_raw_msg->ya = jai_raw.ya;
        jai_raw_msg->za = jai_raw.za;
        jai_raw_msg->ur = jai_raw.ur;
        jai_raw_msg->ul = jai_raw.ul;
        jai_raw_msg->disired_pit = jai_raw.disired_pit;
        jai_raw_msg->desired_dpit = jai_raw.desired_dpit;
        jai_raw_msg->beta = jai_raw.beta;
        jai_raw_msg->Thr_out = jai_raw.Thr_out;

        raw_pub.publish(jai_raw_msg);
    }
};

} // namespace std_plugins
} // namespace mavros



#endif // MAVROS_JAI_RAW_PLUGIN_H

