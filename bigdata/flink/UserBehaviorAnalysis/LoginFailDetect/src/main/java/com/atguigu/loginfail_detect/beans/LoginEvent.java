package com.atguigu.loginfail_detect.beans;/**
 * Copyright (c) 2018-2028 尚硅谷 All Rights Reserved
 * <p>
 * Project: UserBehaviorAnalysis
 * Package: com.atguigu.loginfail_detect.beans
 * Version: 1.0
 * <p>
 * Created by wushengran on 2020/11/17 14:04
 */

/**
 * @ClassName: LoginEvent
 * @Description:
 * @Author: wushengran on 2020/11/17 14:04
 * @Version: 1.0
 */
public class LoginEvent {
    private Long userId;
    private String ip;
    private String loginState;
    private Long timestamp;

    public LoginEvent() {
    }

    public LoginEvent(Long userId, String ip, String loginState, Long timestamp) {
        this.userId = userId;
        this.ip = ip;
        this.loginState = loginState;
        this.timestamp = timestamp;
    }

    public Long getUserId() {
        return userId;
    }

    public void setUserId(Long userId) {
        this.userId = userId;
    }

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public String getLoginState() {
        return loginState;
    }

    public void setLoginState(String loginState) {
        this.loginState = loginState;
    }

    public Long getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(Long timestamp) {
        this.timestamp = timestamp;
    }

    @Override
    public String toString() {
        return "LoginEvent{" +
                "userId=" + userId +
                ", ip='" + ip + '\'' +
                ", loginState='" + loginState + '\'' +
                ", timestamp=" + timestamp +
                '}';
    }
}
