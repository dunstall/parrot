FROM ubuntu

ARG cluster

COPY functional-test functional-test
RUN echo $cluster
ENV cluster $cluster
CMD ./functional-test $cluster
