library(ggplot2)

data0 <- read.csv("out10.csv", header = T, sep = ",")
data1 <- read.csv("out20.csv", header = T, sep = ",")
data2 <- read.csv("out50.csv", header = T, sep = ",")
data3 <- read.csv("out100.csv", header = T, sep = ",")
data4 <- read.csv("out150.csv", header = T, sep = ",")

data5 <- rbind(data0, data1, data2, data3, data4)
data5$Size <- as.factor(data5$Size)

ggplot(data5, aes(x=Epochs, y=bestAnswer, colour = Size, shape = Size)) +
   geom_line() +
   geom_point()

ggsave("plot.png")