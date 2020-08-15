FROM ubuntu

ARG cluster

COPY functional-test.out functional-test
RUN echo $cluster
ENV cluster $cluster
CMD ./functional-test $cluster
