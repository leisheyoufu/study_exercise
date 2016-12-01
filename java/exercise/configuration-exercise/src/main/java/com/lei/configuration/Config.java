package com.lei.configuration;


import org.apache.commons.configuration2.Configuration;
import org.apache.commons.configuration2.builder.fluent.Configurations;
import org.apache.commons.configuration2.ex.ConfigurationException;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.File;


public class Config {
    static Logger logger = LogManager.getLogger(Config.class.getName());

    public static void main(String argv[]) {
        System.out.println(logger.isDebugEnabled());
        logger.debug("started");
        Configurations configs = new Configurations();
        try
        {
            Configuration config = configs.properties(new File("database.properties"));
            String dbHost = config.getString("database.host");
            logger.info("database host is " + dbHost);
            System.out.println(dbHost);

        }
        catch (ConfigurationException cex)
        {
            logger.error("Configuration error");
        }
    }
}
