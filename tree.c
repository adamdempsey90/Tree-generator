#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Node {

	Node *parent, *sibling, *daughter;
	double cm[3], mass, bounds[6];
	int *plist;
	int numparts;

} Node;


typedef struct Particle {

	double pos[3], mass;
	Node *leaf;

} Particle;

Particle *fld;

int main(void) {
	int N=128;
	double box_dim[6];
	
	
	fld=(Particle *)malloc(sizeof(Particle)*N);
	init_particles(N, box_dim);
	
	Node *root=(Node *)malloc(sizeof(Node));
	init_tree(N,box_dim,root);


	free_tree(root);
	free(fld)
}

void init_tree(int N,double *box_dim, Node *root) {
	int i,j;
	
	root->parent=NULL;
	root->sibling=NULL;
	root->numparts=N;
	root->plist=(int *)malloc(sizeof(int)*(root->numparts));

	for(i=0;i<6;i++) root->bounds[i] = box_dim[i];
	
	for(i=0;i<N;i++)	root->plist[i] = i;
	calc_cm(root->plist,root->numparts,&(root->cm[0]),&(root->mass));
	
	
	if (numpats>1) split_node(root,N)


	return;
}

void split_node(Node *parent, int N) {
	int i,j,InBounds;
	Node *daughters[8];
	double midx,midy,midz;
	
	midx = .5*(parent->bounds[0] + parent->bounds[1]);
	midy = .5*(parent->bounds[2] + parent->bounds[3]);	
	midz = .5*(parent->bounds[4] + parent->bounds[5]);
	
	daughters[0] = (Node *)malloc(sizeof(Node));
	daughters[0]->bounds[0] = parent->bounds[0];
	daughters[0]->bounds[1] = midx;
	daughters[0]->bounds[2] = parent->bounds[2];
	daughters[0]->bounds[3] = midy;
	daughters[0]->bounds[4] = parent->bounds[4];
	daughters[0]->bounds[5] = midz;
	
	
	daughters[1] = (Node *)malloc(sizeof(Node));
	daughters[1]->bounds[0] = midx
	daughters[1]->bounds[1] = parent->bounds[1];
	daughters[1]->bounds[2] = parent->bounds[2];
	daughters[1]->bounds[3] = midy;
	daughters[1]->bounds[4] = parent->bounds[4];
	daughters[1]->bounds[5] = midz;

	daughters[2] = (Node *)malloc(sizeof(Node));
	daughters[2]->bounds[0] = midx
	daughters[2]->bounds[1] = parent->bounds[1];
	daughters[2]->bounds[2] = midy;
	daughters[2]->bounds[3] = parent->bounds[3];
	daughters[2]->bounds[4] = parent->bounds[4];
	daughters[2]->bounds[5] = midz;

	daughters[3] = (Node *)malloc(sizeof(Node));
	daughters[3]->bounds[0] = parent->bounds[0];
	daughters[3]->bounds[1] = midx;
	daughters[3]->bounds[2] = midy;
	daughters[3]->bounds[3] = parent->bounds[3];
	daughters[3]->bounds[4] = parent->bounds[4];
	daughters[3]->bounds[5] = midz;
	
	
	daughters[4] = (Node *)malloc(sizeof(Node));
	daughters[4]->bounds[0] = parent->bounds[0];
	daughters[4]->bounds[1] = midx;
	daughters[4]->bounds[2] = parent->bounds[2];
	daughters[4]->bounds[3] = midy;
	daughters[4]->bounds[4] = midz;
	daughters[4]->bounds[5] = parent->bounds[5];
	
	
	daughters[5] = (Node *)malloc(sizeof(Node));
	daughters[5]->bounds[0] = midx
	daughters[5]->bounds[1] = parent->bounds[1];
	daughters[5]->bounds[2] = parent->bounds[2];
	daughters[5]->bounds[3] = midy;
	daughters[5]->bounds[4] = midz;
	daughters[5]->bounds[5] = parent->bounds[5];

	daughters[6] = (Node *)malloc(sizeof(Node));
	daughters[6]->bounds[0] = midx
	daughters[6]->bounds[1] = parent->bounds[1];
	daughters[6]->bounds[2] = midy;
	daughters[6]->bounds[3] = parent->bounds[3];
	daughters[6]->bounds[4] = midz;
	daughters[6]->bounds[5] = parent->bounds[5];

	daughters[7] = (Node *)malloc(sizeof(Node));
	daughters[7]->bounds[0] = parent->bounds[0];
	daughters[7]->bounds[1] = midx;
	daughters[7]->bounds[2] = midy;
	daughters[7]->bounds[3] = parent->bounds[3];
	daughters[7]->bounds[4] = midz;
	daughters[7]->bounds[5] = parent->bounds[5];	

	for(i=0;i<8;i++) {
		daughters[i]->parent = parent;
		if (i>0) daughters[i]->prevsibling = daughters[i-1];
		if (i<7) daughters[i]->nextsibling = daughters[i+1];
		daughters[i]->plist = (int *)malloc(sizeof(int)*(parent->numparts));
		daughters[i]->numparts = 0;
	}
	
	for(i=0;i<parent->numparts;i++) {
		for(j=0;j<8;j++) {
			InBounds=test_particle(fld[parents->plist[i]]->pos,daughters[j]->bounds);
			if (Inbounds==1) {
				daughters[i]->plist[daughters[i]->numparts] = parent->plist[i];
				daughters[i]->nummparts++;
				break;
			}
	}
	
	for(i=0;i<8;i++) {
		realloc(daughters[i]->plist,sizeof(int)*(daughters[i]->numparts));
		if	(daughters->numparts>1) {
			split_node(daughters[i],daughters[i]->numparts);
		}
		else {
		
			if (daughters->numparts==0) {
				if (daughters->prevsibling!=NULL) {
						daughters[i-1]->nextsibling=NULL;
				}
				if (daughters->nextsibling!=NULL) {
						daughters[i+1]->prevsibling=NULL;
				}
				free(daughters[i]->plist);
				free(daughters[i]);
			}
		}
		
	}
	return;
}
int test_particle(double pos[3], double bounds[6]) {
	
	if ((pos[0]>bounds[0]) && (pos[0]<=bounds[1]) 
				&& (pos[1]>bounds[2]) && (pos[1]<=bounds[3]) 
				&& (pos[2]>bounds[4]) && (pos[2]<=bounds[5])) 
	{			
		return 1			
	}
	else return 0;
}

void calc_cm(int *plist, int numparts, double *cm, double *totmass) {
	int i;
	mass=0;
	cm[0]=0; cm[1]=0; cm[2]=0;
	if (numparts!=0) {
		for(i=0;i<numparts) {
			cm[0] += fld[plist[i]]->mass * fld[plist[i]]->pos[0];
			cm[1] += fld[plist[i]]->mass * fld[plist[i]]->pos[1];
			cm[2] += fld[plist[i]]->mass * fld[plist[i]]->pos[2];
			mass += fld[plist[i]]->mass;
		}
	
		cm[0] /= mass;
		cm[1] /= mass;
		cm[2] /= mass
	}
	return;

} 
void init_particles(int N) {
	int i;
	
	
	while (i<N) {
	
	
	
	
	
	
	}

}

double distance(double p1[3], double p2[3]) {
	
	return sqrt(pow(p1[0]-p2[0],2)+pow(p1[1]-p2[1],2)+pow(p1[2]-p2[2],2));

}