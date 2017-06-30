require(timevis)

drawGantChart<-function(filename, machine)
{
	d1<-read.table(filename, header=TRUE, sep="|")
	grs<-data.frame(id = 0:(machine-1), content = c(0:(machine-1)))
	timevis(d1, grs)
}

