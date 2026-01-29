#ifndef MAVROS_JAI_OUT_PLUGIN_H
#define MAVROS_JAI_OUT_PLUGIN_H

#include <mavros/mavros_plugin.h>
#include <mavros_msgs/JAIOut.h>
#include <pluginlib/class_list_macros.h>
#include <mavros_msgs/JAISET.h>

namespace mavros {
namespace std_plugins {
class JAIOutPlugin : public plugin::PluginBase {        
    public:
        JAIOutPlugin() : PluginBase(), nh("~") { }
        void initialize(UAS &uas_) override {
        PluginBase::initialize(uas_);
        jai_cmd_sub = nh.subscribe("/Jai_command", 10,&JAIOutPlugin::Topic_cb,this);
        // jai_test=nh.createTimer(ros::Duration(1.0),&JAIOutPlugin::time_cb,this);
        }
    private:
    ros::NodeHandle nh;
    ros::Subscriber jai_cmd_sub;
    ros::Timer jai_test;
    void Topic_cb(const mavros_msgs::JAIOut::ConstPtr &msg){
        mavlink::common::msg::JAI_OUT sp = {};
        sp.rc_state=msg->rc_state;
        sp.pit_pwm=msg->pit_pwm;
        sp.wh_r=msg->wh_r;
        sp.wh_l=msg->wh_l;
        sp.u_thr=msg->u_thr;
        UAS_FCU(m_uas)->send_message_ignore_drop(sp);
    }
    void time_cb(ros::TimerEvent&){
        // mavlink::common::msg::JAI_OUT sp = {};
        // sp.rc_state=1;
        // sp.pit_pwm=500;
        // sp.wh_r=0.3;
        // sp.wh_l=0.3;
        // sp.u_thr=0.3;
        // UAS_FCU(m_uas)->send_message_ignore_drop(sp);

    }
    Subscriptions get_subscriptions() override {
        return { /* No subscriptions needed for this example */ };
    }
};

}
}

#endif 